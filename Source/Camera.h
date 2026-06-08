#pragma once
#include "DxLib.h"

class Object3D;

class Camera
{
public:
	enum CameType {
		None3D = 0,	//(デフォルト)設定なし
	};

public:

	Camera();
	~Camera();

	void Initialize();
	void Update(float _deltaTime);
	void UpdateRotation();

	void Shake();	// 画面揺れ
	void SetupShake(float time, float width, float angleSpeed, float stepTime = 1.0f);

	//座標取得
	VECTOR GetPosition() { return mvPosition; }
	void SetPosition(VECTOR _pos) { mvPosition = _pos; }

	VECTOR GetLookAtPosition() { return mvLookAtPosition; }	//注視点取得

private:
	
	float mfHorizontalAngle;	//水平方向アングル
	float mfVerticalAngle;		//垂直方向アングル

	VECTOR mvPosition;			//カメラ座標
	VECTOR mvLookAtPosition;	//カメラの注視点座標

	Object3D* mpTarget;			//カメラを向ける対象


	//画面揺れ関係
	int mnShakeTime;
	int mnShakeTimeCount;
	float mfShakeAngle;
	float mfShakeTimeCounter;
	float mfShakeTime;
	float mfShakeWidth;
	float mfShakeAngleSpeed;
	float mfStepTime;
	VECTOR mvShakePosition;

};