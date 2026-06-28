#include "DxLib.h"
#include "SeparateModelAnimation.h"

#include "ResourceManager.h"

SeparateModelAnimation::SeparateModelAnimation(int modelHandle)
    : mnModelHandle(modelHandle) {
    int moveAnimFrameIndex = MV1SearchFrame(mnModelHandle, "root");             // アニメーションで移動をしているフレーム番号を検索する
    MV1SetFrameUserLocalMatrix(mnModelHandle, moveAnimFrameIndex, MGetIdent()); // アニメーションに付与されている移動を無効にする
}

SeparateModelAnimation::~SeparateModelAnimation() {
    //全てのアニメーションハンドルを解放する
    for (auto& animationInfo : mAnimationInfoList) {
        if (animationInfo.mnAnimationHandle != -1) {
            MV1DeleteModel(animationInfo.mnAnimationHandle);
        }
    }
}

void SeparateModelAnimation::Update(float _deltaTime) {
    UpdateBlend();
    UpdateCurrentAnimation();
    UpdateOldAniamtion();
}

void SeparateModelAnimation::UpdateCurrentAnimation() {
    //-- 現アニメーションの処理 --//
    if (mnAnimationIndex != -1) {
        mfNowAnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mnAnimationIndex);     // 総再生時間の取得
        mfAnimationTime += DEFAULT_ANIMATION_SPEED;  // 速度補正追加,アニメーションの秒数を進める

        //アニメーションを再生しきった場合
        if (mfAnimationTime > mfNowAnimTotalTime) {

            // ループしない設定であれば
            if (!mbLoop) {
                // 次のモーションが設定されていない場合
                if (mnLoopFinishState == ANIMATION_MAX) {
                    mbLoopFinish = true;    // モーションはこれ以上進めず、処理を中断させる
                    return;
                }

                ChangeAnimation(mnLoopFinishState);  // ループ終了時のモーションへ変更
                SetAnimationBlend(false);   // ブレンドはしない

                mfNowAnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mnAnimationIndex);     // 変更されたので改めて総再生時間をとっておく
            }
            mfAnimationTime = 0.0f; //現再生時間をリセット
        }

        MV1SetAttachAnimTime(mnModelHandle, mnAnimationIndex, mfAnimationTime); // モーションを反映
        MV1SetAttachAnimBlendRate(mnModelHandle, mnAnimationIndex, mfAnimBlendRate);    // ブレンド率を設定
    }
}

void SeparateModelAnimation::UpdateOldAniamtion() {
    //-- 前アニメーションの処理 --//
    if (mnOldAnimationIndex != -1) {
        float fAnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mnOldAnimationIndex); // 総再生時間の取得
        mfOldAnimationTime += DEFAULT_ANIMATION_SPEED * mfAnimationSpeedScale;  // 速度補正追加,アニメーションの秒数を進める

        // アニメーションが回り切った場合
        if (mfOldAnimationTime > fAnimTotalTime) {
            mfOldAnimationTime = 0.0f;  //アニメーション再生時間をリセット
        }

        MV1SetAttachAnimTime(mnModelHandle, mnOldAnimationIndex, mfOldAnimationTime);   // モーションを反映
        MV1SetAttachAnimBlendRate(mnModelHandle, mnOldAnimationIndex, 1.0f - mfAnimBlendRate);  // ブレンド率を設定
    }
}

void SeparateModelAnimation::UpdateBlend() {
    if (mfAnimBlendRate < 1.0f) {
        mfAnimBlendRate += 0.025f;    // += 0.1f はブレンド速度。自由に変えてもok

        //ブレンド中にアニメーション割合が超えてしまった場合
        if (mfAnimBlendRate > 1.0f) {
            mfAnimBlendRate = 1.0f; //完全にアニメーションを切り替える
        }
    }
}
    
    
// モーション切り替え
void SeparateModelAnimation::ChangeAnimation(AnimationState state, int index, bool isForce) {
    // 切り替えようとしているモーションがすでに設定されている場合
    if (mnState == state && !isForce)   return; //以降スルー

    //-- ↓モーションが変更されている場合 --//

    mnState = state;    // 切り替え先の番号を保持
    mfAnimationSpeedScale = 1.0f;   // 速度をデフォルトでは1.0fにしておく

    // ループ情報の初期化
    mbLoop = true;  // 設定が特にない場合はループさせる
    mnLoopFinishState = AnimationState::ANIMATION_MAX;  // ループ終了時のモーションは特になし
    mbLoopFinish = false;

    // １つ前のモーションが有効状態であれば
    if (mnOldAnimationIndex != -1) {
        MV1DetachAnim(mnModelHandle, mnOldAnimationIndex);   // モーションのデタッチ（取り外す）
        mnOldAnimationIndex = -1;   //前アニメーションのインデックスを無効化
    }

    mnOldAnimationIndex = mnAnimationIndex;  // 現在のモーション状態を前アニメーションへスライド
    mfOldAnimationTime = mfAnimationTime;    // 現アニメーション再生時間を引き継ぐ

    mnAnimationIndex = MV1AttachAnim(mnModelHandle, index, GetAnimationHandle(state), TRUE);    //現アニメーションのアタッチ
    mfAnimationTime = 0.0f; // 再生時間の初期化

    // ブレンド状態を初期化
    // ブレンド率は、古いモーションが有効でない場合は1.0f（ブレンドしない状態）にしておく
    mfAnimBlendRate = (mnOldAnimationIndex == -1 ? 1.0f : 0.0f);
}


// モーションのブレンド設定
void SeparateModelAnimation::SetAnimationBlend(bool isBlend) {
    //ブレンドする場合
    if (isBlend) {
        // ブレンド率は、古いモーションが有効でない場合は1.0f（ブレンドしない状態）にしておく
        mfAnimBlendRate = (mnOldAnimationIndex == -1 ? 1.0f : 0.0f);
    }

    //ブレンドしない場合
    else {
        mfAnimBlendRate = 1.0f;  // ブレンド率を現アニメーション100%に設定

        // ブレンドする必要がないので、古いモーションはデタッチしておく
        if (mnOldAnimationIndex != -1) {
            MV1DetachAnim(mnModelHandle, mnOldAnimationIndex);  //前アニメーションをデタッチ
            mnOldAnimationIndex = -1;   //前アニメーションのインデックスを無効化
        }
    }
}

// モーション追加
void SeparateModelAnimation::AddAnimation(AnimationState state, const std::string& filename) {
    int handle = ResourceManager::GetInstance().LoadModel(filename.c_str());    // モーションモデル読み込み
    if (handle == -1) return;                       //アニメーションハンドルが読み込みに失敗した場合、以降スルー

    mAnimationInfoList.push_back(AnimationInfo(state, handle)); //AnimationInfo内のコンストラクタでハンドルの紐づけを行う

    // NEUTRALモーション（待機モーション）が追加されたらモーション変更処理をしておく
    if (state == AnimationState::ANIMATION_NEUTRAL) {
        ChangeAnimation(AnimationState::ANIMATION_NEUTRAL);  // 初期状態は待機モーションにしておく
    }
}

// 対応したモーションハンドルの取得
int SeparateModelAnimation::GetAnimationHandle(AnimationState state) {
    for (auto& animationInfo : mAnimationInfoList) {
        if (animationInfo.mState == state) return animationInfo.mnAnimationHandle;  //目的のハンドルを返す
    }
    return -1;  //見つからなかった場合、無効値を返す
}

// モーション進捗率の取得
float SeparateModelAnimation::GetAnimationProgressRate() {
    return mfAnimationTime / mfNowAnimTotalTime;
}