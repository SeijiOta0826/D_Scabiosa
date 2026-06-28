#pragma once

// 
// ★New★
// 新規追加ファイル
//

#include <string>
#include <vector>
#include <memory>
#include "ModelUtility.h"

class SeparateModelAnimation
{
public:
    SeparateModelAnimation(int modelHandle);   // コンストラクタ
    ~SeparateModelAnimation();  // デストラクタ

    void Update(float _deltaTime);  // 更新

    void ChangeAnimation(AnimationState state, int index = 0, bool isForce = false); // モーション切り替え処理

    void UpdateCurrentAnimation();
    void UpdateOldAniamtion();
    void UpdateBlend();

    void AddAnimation(AnimationState state, const std::string& filename);   //モーションの追加

    int GetAnimationHandle(AnimationState state);   // 対応したモーションハンドルの取得

    // ループ設定
    void SetLoop(bool isLoop) { mbLoop = isLoop; }
    // ループ終了時に再生するモーション
    void SetLoopFinishState(AnimationState state) { mnLoopFinishState = state; }
    // モーションのブレンド設定
    void SetAnimationBlend(bool isBlend);
    // ★New★
    // アニメーション速度補正の設定
    void SetAnimationSpeed(float speed) { mfAnimationSpeedScale = speed; }

    AnimationState GetNowState() { return mnState; }    // 現在再生されているモーションの取得
    bool IsLoopFinish() { return mbLoopFinish; }    // モーションのループが終了しているかどうか
    float GetAnimationProgressRate();   // モーション進捗率の取得


private:
    int mnModelHandle;  // モデルのハンドル

    float mfAnimationTime = 0.0f;       // 再生しているモーションの現在の再生時間
    int mnAnimationIndex = -1;          // 再生しているモーションのインデックス
    float mfOldAnimationTime = 0.0f;    // 1つ前のモーション再生時間
    int mnOldAnimationIndex = -1;       // １つ前のモーションのインデックス

    float mfAnimBlendRate = 1.0f;       // モーションの切り替わり度合

    AnimationState mnState = AnimationState::ANIMATION_MAX;             // 現在再生しているモーションの番号
    AnimationState mnLoopFinishState = AnimationState::ANIMATION_MAX;   // ループが終わった時に再生したいモーション番号

    bool mbLoop = true;            // モーションをループさせるかどうか
    bool mbLoopFinish = false;     // モーションループが終わったかどうか

    float mfAnimationSpeedScale = 1.0f;    // モーション速度係数
    float mfNowAnimTotalTime = 0.0f;       // 現在のモーションの総再生時間

    std::vector<AnimationInfo> mAnimationInfoList;  // モーションデータのリスト

private:
    const float DEFAULT_ANIMATION_SPEED = 0.5f; // モーションのデフォルト速度を定義
};