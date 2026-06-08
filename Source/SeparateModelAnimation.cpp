#include "DxLib.h"
#include "SeparateModelAnimation.h"

SeparateModelAnimation::SeparateModelAnimation(int modelHandle)
    : mnModelHandle(modelHandle)
    , mfAnimationTime(0.0f)
    , mnAnimationIndex(-1)
    , mfOldAnimationTime(0.0f)
    , mnOldAnimationIndex(-1)
    , mfAnimBlendRate(1.0f)
    , mnState(AnimationState::ANIMATION_MAX)    // 最初は最大値としておく
    , mbLoop(true)
    , mnLoopFinishState(AnimationState::ANIMATION_MAX)
    , mbLoopFinish(false)
    , mAnimationInfoList() {
    int moveAnimFrameIndex = MV1SearchFrame(mnModelHandle, "root"); // アニメーションで移動をしているフレーム番号を検索する
    MV1SetFrameUserLocalMatrix( mnModelHandle,moveAnimFrameIndex, MGetIdent()); // アニメーションに付与されている移動を無効にする
}

SeparateModelAnimation::~SeparateModelAnimation() {

    //-- 追加読み込みしたモーションの削除 --//
    if (!mAnimationInfoList.empty()) {
        for (auto itr = mAnimationInfoList.begin();
            itr != mAnimationInfoList.end(); ) {
            auto temp = *itr;   //アニメーションデータのアドレスをローカルへ一時避難

            itr = mAnimationInfoList.erase(itr);    //アニメーションデータを消去
            MV1DeleteModel(temp->mnAnimationHandle);        //アニメーションのハンドルを消去

            delete temp;    //ローカルデータ解放
            temp = nullptr; //一応null
        }
    }
}

// 更新処理
void SeparateModelAnimation::Update(float _deltaTime){

    //-- モーションのブレンド率を進める --//

    //ブレンド中の場合
    if (mfAnimBlendRate < 1.0f) {
        mfAnimBlendRate += 0.1f;    // += 0.1f はブレンド速度。自由に変えてもok

        //ブレンド中にアニメーション割合が超えてしまった場合
        if (mfAnimBlendRate > 1.0f) {
            mfAnimBlendRate = 1.0f; //完全にアニメーションを切り替える
        }
    }


    //モーションの更新
    if (mnAnimationIndex != -1) {
        mfNowAnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mnAnimationIndex);     // 総再生時間の取得

        mfAnimationTime += DEFAULT_ANIMATION_SPEED * mfAnimationSpeedScale;  // 速度補正追加

        // ★New★
        // fAnimTotalTime をメンバ変数に変更
        // ループさせる
        if (mfAnimationTime > mfNowAnimTotalTime)
        {
            // ループしない設定であれば
            if (!mbLoop)
            {
                // 次のモーションが設定されていない場合
                if (mnLoopFinishState == ANIMATION_MAX)
                {
                    // モーションはこれ以上進めず、処理を中断させる
                    mbLoopFinish = true;
                    return;
                }

                // ループ終了時のモーションへ変更
                ChangeAnimation(mnLoopFinishState);
                // ブレンドはしない
                SetAnimationBlend(false);
                // ★New★
                // fAnimTotalTime をメンバ変数に変更
                // 変更されたので改めて総再生時間をとっておく
                mfNowAnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mnAnimationIndex);
            }

            mfAnimationTime = 0.0f;
        }

        // モーションを反映
        MV1SetAttachAnimTime(mnModelHandle, mnAnimationIndex, mfAnimationTime);

        // ブレンド率を設定
        MV1SetAttachAnimBlendRate(mnModelHandle, mnAnimationIndex, mfAnimBlendRate);
    }


    // １つ前のモーションを更新
    float fAnimTotalTime = 0.0f;
    if (mnOldAnimationIndex != -1)
    {
        // 総再生時間の取得
        fAnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mnOldAnimationIndex);

        // モーションを進める
        mfOldAnimationTime += DEFAULT_ANIMATION_SPEED * mfAnimationSpeedScale;

        // ループさせる
        if (mfOldAnimationTime > fAnimTotalTime)
        {
            mfOldAnimationTime = 0.0f;
        }

        // モーションを反映
        MV1SetAttachAnimTime(mnModelHandle, mnOldAnimationIndex, mfOldAnimationTime);

        // ブレンド率を設定
        MV1SetAttachAnimBlendRate(mnModelHandle, mnOldAnimationIndex, 1.0f - mfAnimBlendRate);
    }
}
    // ★New★
    // 強制切り替えの引数を追加(isForce)
    // モーション切り替え
void SeparateModelAnimation::ChangeAnimation(AnimationState state, int index, bool isForce)
{
    // 切り替えようとしているモーションがすでに設定されている場合
    if (mnState == state && !isForce)
    {
        return;     // 何もしない
    }

    // 切り替え先の番号を保持
    mnState = state;

    // ★New★
    // 速度をデフォルトでは1.0fにしておく
    mfAnimationSpeedScale = 1.0f;

    // ループ情報の初期化
    mbLoop = true;  // 設定が特にない場合はループさせる
    mnLoopFinishState = AnimationState::ANIMATION_MAX;  // ループ終了時のモーションは特になし
    mbLoopFinish = false;

    // １つ前のモーションが有効状態であれば
    if (mnOldAnimationIndex != -1)
    {
        // モーションのデタッチ（取り外す）
        MV1DetachAnim(mnModelHandle, mnOldAnimationIndex);
        mnOldAnimationIndex = -1;
    }

    // 現在のモーション状態を保持する
    mnOldAnimationIndex = mnAnimationIndex;
    mfOldAnimationTime = mfAnimationTime;

    // モーションのアタッチ
    mnAnimationIndex = MV1AttachAnim(mnModelHandle, index, GetAnimationHandle(state), TRUE);

    // 再生時間の初期化
    mfAnimationTime = 0.0f;

    // ブレンド状態を初期化
    // ブレンド率は、古いモーションが有効でない場合は1.0f（ブレンドしない状態）にしておく
    mfAnimBlendRate = (mnOldAnimationIndex == -1 ? 1.0f : 0.0f);
}


// モーションのブレンド設定
void SeparateModelAnimation::SetAnimationBlend(bool isBlend)
{
    if (isBlend)    // ブレンドする場合
    {
        // ブレンド率は、古いモーションが有効でない場合は1.0f（ブレンドしない状態）にしておく
        mfAnimBlendRate = (mnOldAnimationIndex == -1 ? 1.0f : 0.0f);
    }
    else    // ブレンドしない場合
    {
        // ブレンドしない状態にする
        mfAnimBlendRate = 1.0f;

        // ブレンドする必要がないので、古いモーションはデタッチしておく
        if (mnOldAnimationIndex != -1)
        {
            MV1DetachAnim(mnModelHandle, mnOldAnimationIndex);
            mnOldAnimationIndex = -1;
        }
    }
}

// モーション追加
void SeparateModelAnimation::AddAnimation(AnimationState state, std::string filename)
{
    // モーションモデル読み込み
    int handle = MV1LoadModel(filename.c_str());

    if (handle == -1)
    {
        return;
    }

    // AnimationState と読み込んだハンドルの紐づけ
    AnimationInfo* pInfo = new AnimationInfo();
    pInfo->mState = state;
    pInfo->mnAnimationHandle = handle;
    mAnimationInfoList.push_back(pInfo);

    // NEUTRALモーション（待機モーション）が追加されたらモーション変更処理をしておく
    if (state == AnimationState::ANIMATION_NEUTRAL)
    {
        // 初期状態は待機モーションにしておく
        ChangeAnimation(AnimationState::ANIMATION_NEUTRAL);
    }
}

// 対応したモーションハンドルの取得
int SeparateModelAnimation::GetAnimationHandle(AnimationState state)
{
    // そもそも空っぽの場合は探さない
    if (mAnimationInfoList.empty())
    {
        return -1;
    }

    for (auto itr = mAnimationInfoList.begin(); itr != mAnimationInfoList.end(); itr++)
    {
        auto temp = *itr;

        // 対応するモーションハンドルがあればそれを返す
        if (temp->mState == state)
        {
            return temp->mnAnimationHandle;
        }
    }

    // 見つからなかったら-1を返す
    return -1;
}


bool SeparateModelAnimation::AttackCheack()
{
    for (auto index_anim : mAttackCheakInfoList)
    {
        //効果指定stateを再生している場合
        if (index_anim->mnState == mnState)
        {
            if (index_anim->mfStartTime < mfAnimationTime
                && mfAnimationTime < index_anim->mfFinishTime)
            {
                if (!index_anim->mbIsAttacked)
                {
                    index_anim->mbIsAttacked = true;
                    return true;
                }
            }

            else
            {
                index_anim->mbIsAttacked = false;
                return false;
            }
        }

        //指定外のstateは一応初期化しておく
        else
        {
            index_anim->mbIsAttacked = false;
        }
    }

    return false;
}

// ★New★
// モーション進捗率の取得
float SeparateModelAnimation::GetAnimationProgressRate()
{
    return mfAnimationTime / mfNowAnimTotalTime;
}


//攻撃判定に扱う
void SeparateModelAnimation::AddAttackCheckInfo(
    AnimationState mnState, //攻撃アニメーション
    float mfStartTime,  //判定開始
    float mfFinishTime // 判定終了
)
{
    AttackCheckInfo* pInfo = new AttackCheckInfo;
    pInfo->mnState = mnState;
    pInfo->mfStartTime = mfStartTime;
    pInfo->mfFinishTime = mfFinishTime;
    pInfo->mbIsAttacked = false;

    mAttackCheakInfoList.push_back(pInfo);
}