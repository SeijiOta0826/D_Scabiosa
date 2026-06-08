#pragma once
#include "DxLib.h"
#include <string>
#include "ModelUtility.h"
#include "ModelAnimation.h"
#include "SeparateModelAnimation.h"

class AttachmentModel;

class Model
{
public:

	Model(std::string filename,VECTOR initPos, bool isSeparateAnimation = false);
	~Model();

	void Update(float _deltaTime);	//更新処理
	void Draw();	//描画処理

	void ChangeAnimation(AnimationState state, bool isForce = false);	// アニメーション切り替え

	//ループ設定
	void SetLoop(bool loop);
	void SetLoopFinishState(AnimationState state);
	bool IsAnimationLoopFinish();	//アニメーションのループが終了しているかどうか

	void SetAnimationBlend(bool isBlend);	//アニメーションのブレンド設定

	AnimationState GetNowState();	//現在再生されているアニメーションの取得

	//アタッチメントを追加
	void AddAttachment(std::string filename, std::string attachFrameName);
	VECTOR GetAttachmentPosition();	//アタッチモデルの座標を取得

   
	void SetAnimationSpeedScale(float speed);	// アニメーション速度補正
	float GetAnimationProgressRate();	// アニメーション進捗率取得

	
	bool IsAnimationAttack();	// 攻撃モーション中かどうか

	//inPlace関係
	void SetupInitializeMatrix(std::string rootFrameName);	// 初期行列の設定
	bool ValidRootFrameIndex();	// 有効なフレームかどうかの判定

	//座標アクセサ
	void SetPosition(VECTOR pos) { mvPosition = pos; }
	VECTOR GetPosition() { return mvPosition; }

	//回転値アクセサ
	void SetRotation(VECTOR rot){mvRotation = rot;}
	VECTOR GetRotation(){return mvRotation;}
	
	void SetScale(VECTOR scale) { MV1SetScale(mnHandle, scale); }	//拡大処理

	//モデルデータ(int)のゲッター
	int GetHandleData() { return mnHandle; }


   // アニメーションデータの追加
   // note: SeparateModelAnimation クラスへの橋渡し関数
	void AddAnimation(AnimationState state, std::string filename);
	SeparateModelAnimation* GetSparateAnimData() { return mpSeparateAnimation;}	//セパレートアニメーションデータの取得



private:
	int mnHandle;	//ハンドルデータ
	
	VECTOR mvPosition;	//座標
	VECTOR mvRotation;	//回転
	VECTOR mvScale;	//モデルの拡大値

	int mnChangeTextureHandle;

	MATRIX mmInitializeMatrix;  // ★New★ // モデル内部で移動をしている（であろう）フレームの初期行列
	int mnRootFrameIndex;       // ★New★ // モデル内部で移動をしている（であろう）フレームのインデックス（初期値 -1）

	//モデルアニメーションクラスのポインタ
	ModelAnimation* mpAnimation;

	// 分割読み込みバージョンのモデルアニメーションクラスのポインタ
	SeparateModelAnimation* mpSeparateAnimation;

	//アタッチモデル(複数持たせたい場合は std::vector や配列で管理すると良い)
	AttachmentModel* mpAttachment;
};