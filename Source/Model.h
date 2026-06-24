#pragma once
#include "DxLib.h"
#include <string>
#include "ModelUtility.h"
#include "SeparateModelAnimation.h"
#include "Vector3.h"

class AttachmentModel;

class Model
{
public:

	Model(const std::string& filename, const Vector3& initPos, bool isSeparateAnimation = false);
	~Model();

	void Update(float _deltaTime);	//更新処理
	void Draw();	//描画処理

	void ChangeAnimation(AnimationState state, bool isForce = false);	// アニメーション切り替え

	void SetLoop(bool loop);						//ループ設定
	void SetLoopFinishState(AnimationState state);	//ループが終わった時に再生したいアニメーション番号
	bool IsAnimationLoopFinish();					//アニメーションのループが終了しているかどうか

	void SetAnimationBlend(bool isBlend);	//アニメーションのブレンド設定

	AnimationState GetNowState();	//現在再生されているアニメーションの取得


	void AddAttachment(std::string filename, std::string attachFrameName);	//アタッチメントを追加
	Vector3 GetAttachmentPosition();											//アタッチモデルの座標を取得

   
	void SetAnimationSpeedScale(float speed);	// アニメーション速度補正
	float GetAnimationProgressRate();	// アニメーション進捗率取得

	
	//-- アニメーションによる移動を防ぐ関係 --//
	void SetupInitializeMatrix(std::string rootFrameName);	// 初期行列の設定
	bool ValidRootFrameIndex();	// 有効なフレームかどうかの判定

	//座標アクセサ
	void SetPosition(Vector3 pos) { mvPosition = pos; }
	Vector3 GetPosition() { return mvPosition; }

	//回転値アクセサ
	void SetRotation(Vector3 rot){mvRotation = rot;}
	Vector3 GetRotation(){return mvRotation;}
	
	void SetScale(Vector3 scale) { MV1SetScale(mnHandle, scale.ToDxVector()); }	//拡大処理

	//モデルデータ(int)のゲッター
	int GetHandleData() { return mnHandle; }


   // アニメーションデータの追加
   // note: SeparateModelAnimation クラスへの橋渡し関数
	void AddAnimation(AnimationState state, std::string filename);
	SeparateModelAnimation* GetSparateAnimData() { return mpSeparateAnimation;}	//セパレートアニメーションデータの取得



private:
	int mnHandle;	//ハンドルデータ
	
	Vector3 mvPosition;	//座標
	Vector3 mvRotation;	//回転
	Vector3 mvScale;	//モデルの拡大値

	int mnChangeTextureHandle;

	MATRIX mmInitializeMatrix;  // ★New★ // モデル内部で移動をしている（であろう）フレームの初期行列
	int mnRootFrameIndex;       // ★New★ // モデル内部で移動をしている（であろう）フレームのインデックス（初期値 -1）


	// 分割読み込みバージョンのモデルアニメーションクラスのポインタ
	SeparateModelAnimation* mpSeparateAnimation;

	//アタッチモデル(複数持たせたい場合は std::vector や配列で管理すると良い)
	AttachmentModel* mpAttachment;
};