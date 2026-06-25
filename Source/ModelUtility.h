#pragma once

// 
// ★New★
// 新規追加ファイル
//

class Object3D;

// アニメーションの切り替え番号
enum AnimationState
{
    ANIMATION_NEUTRAL = 0,  // アイドル
    ANIMATION_WAIT,         // 待機
    ANIMATION_WALKING,      // 歩き
    ANIMATION_RUN,          // 走り
    ANIMATION_JUMP_IN,      // ジャンプ開始
    ANIMATION_JUMP_FALL,    // ジャンプ中
    ANIMATION_JUMP_OUT,     // 着地時
    ANIMATION_ATTACK,       //攻撃(1)
    ANIMATION_ATTACK_2,     //攻撃(2)
    ANIMATION_ATTACK_3,     //攻撃(3)
    ANIMATION_GUARD,        //ガード
    ANIMATION_PARRY,        //パリィ
    ANIMATION_CLIMD_UP,     //壁登り(上昇)
    ANIMATION_CLIMD_DOWN,   //壁登り(下降)


    ANIMATION_DYING,        // 死亡時
 
    ANIMATION_MAX
};

// ★New★
// 分割されているアニメーションのデータ
struct AnimationInfo
{
    AnimationState mState;
    int mnAnimationHandle;

    AnimationInfo(AnimationState _state, int _handle)
        :mState(_state)
        , mnAnimationHandle(_handle) {
    }

    ~AnimationInfo() {
        if (mnAnimationHandle != -1) {
            MV1DeleteModel(mnAnimationHandle);
        }
    }
};
