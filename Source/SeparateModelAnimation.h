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

    // ★New★
    // note: mixamo でモーションをダウンロードすると、
    //       0番目のモーションデータはダミーが入っているらしいので、
    //       デフォルトで適用するインデックスを 1 にしておく
    //void ChangeAnimation(AnimationState state, int index = 0); // モーション切り替え処理

    // ★New★
    // 強制切り替えの引数を追加(isForce)
    // 
    // note: mixamo でモーションをダウンロードすると、
    //       0番目のモーションデータはダミーが入っているらしいので、
    //       デフォルトで適用するインデックスを 1 にしておく
    void ChangeAnimation(AnimationState state, int index = 0, bool isForce = false); // モーション切り替え処理

    // ★New★
    // モーションデータの追加
    // note: 分割されているモーションをデータとして登録する。
    void AddAnimation(AnimationState state, const std::string& filename);

    // ★New★
    // 対応したモーションハンドルの取得
    // note: vector配列にデータが格納されているため、
    //       毎回ハンドルを検索する手間が出てきてしまうので、
    //       それを行うための関数。
    int GetAnimationHandle(AnimationState state);


    // ループ設定
    void SetLoop(bool isLoop) { mbLoop = isLoop; }
    // ループ終了時に再生するモーション
    void SetLoopFinishState(AnimationState state) { mnLoopFinishState = state; }
    // モーションのブレンド設定
    void SetAnimationBlend(bool isBlend);
    // ★New★
    // アニメーション速度補正の設定
    void SetAnimationSpeed(float speed) { mfAnimationSpeedScale = speed; }

    // 現在再生されているモーションの取得
    AnimationState GetNowState() { return mnState; }
    // モーションのループが終了しているかどうか
    bool IsLoopFinish() { return mbLoopFinish; }
    // ★New★
    // モーション進捗率の取得
    float GetAnimationProgressRate();



    //攻撃判定関係。
    //Animationクラスに持たせるのはアリなのか審議だが、今回はここで。以下memo
    //①「判定を持たせるアニメーションのState」と「各Stateの判定Rangの時間(始点終点の2つの値)」
    //を収納したリストをコンストラクタで用意
    // 
    //②各State再生時、且つ判定Rang内の場合trueを返すゲッターを作る
    // 
    //③回避判定(Player)で使う。

    void AddAttackCheckInfo(
        AnimationState mnState, //攻撃アニメーション
        float mfStartTime,  //判定開始
        float mfFinishTime // 判定終了
    );

    bool AttackCheack();


private:
    int mnModelHandle;  // モデルのハンドル

    float mfAnimationTime;  // 再生しているモーションの現在の再生時間
    int mnAnimationIndex;   // 再生しているモーションのインデックス

    float mfOldAnimationTime;   // 1つ前のモーション再生時間
    int mnOldAnimationIndex;    // １つ前のモーションのインデックス

    float mfAnimBlendRate;      // モーションの切り替わり度合

    AnimationState mnState; // 現在再生しているモーションの番号

    bool mbLoop;            // モーションをループさせるかどうか
    AnimationState mnLoopFinishState;   // ループが終わった時に再生したいモーション番号
    bool mbLoopFinish;      // モーションループが終わったかどうか


    float mfAnimationSpeedScale;    // ★New★　モーション速度係数
    float mfNowAnimTotalTime;       // ★New★　現在のモーションの総再生時間

    std::vector<AnimationInfo> mAnimationInfoList;  // モーションデータのリスト

private:
    const float DEFAULT_ANIMATION_SPEED = 0.5f; // ★New★　モーションのデフォルト速度を定義
};