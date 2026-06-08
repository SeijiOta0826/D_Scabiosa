#pragma once

#include <string>
#include <vector>
#include "ModelUtility.h"
#include "DxLib.h"

class ModelAnimation
{
public:


public:
	//コンストラクタ
	ModelAnimation(int modelHandle);

	//デストラクタ
	~ModelAnimation();

	//更新
	void Update();

	//アニメーション切り替え処理
	void ChangeAnimation(AnimationState state, int index = 1);

	//ループ設定
	void SetLoop(bool isLoop) { mbLoop = isLoop; }
	//ループ終了時に再生するアニメーション
	void SetLoopFinishState(AnimationState state) { mnLoopFinishState = state; }
	//アニメーションのブレンド設定
	void SetAnimationBlend(bool isBlend);

	//現在再生されているアニメーションの取得
	AnimationState GetNowState() { return mnState; }
	//アニメーションのループが終了しているかどうか
	bool IsLoopFinish() { return mbLoopFinish; }

private:
	//アニメーションをループさせるか
	bool mbLoopFlag;

	//モデルのハンドル
	int mnModelHandle;


	//再生してるアニメーションの現在の再生時間
	float mfAnimationTime;
	//再生しているアニメーションのインデックス
	int mnAnimationIndex;
	

	//各モーションの切り替えを自然に見せるためには
	// モーション対モーションの繋ぎ合わせを考えなければならない。
	// そのために前のモーションの情報をとってくる必要がある
	//1つ前のアニメーション再生時間
	float mfOldAnimationTime;
	//1つ前のアニメーションのインデックス
	int mnOldAnimationIndex;


	//モーションの切り替わり具合
	float mfAnimBlendRate;


	//現在再生しているアニメーションの番号
	AnimationState mnState;

	//モーションをループさせるかどうか
	bool mbLoop;
	//ループが終わった時に再生したいアニメーション番号
	AnimationState mnLoopFinishState;
	//モーションが終わったかどうか
	bool mbLoopFinish;

};