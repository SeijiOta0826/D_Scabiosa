#pragma once
#include "DxLib.h"

class Object3D;

class Camera
{
public:

	Camera();
	~Camera();

	static Camera& GetInstance(); //インスタンスの取得

	void Initialize();
	void Finalize();
	void Update(float _deltaTime);
	void UpdateRotation();

	void Shake();	// 画面揺れ
	void SetupShake(float time, float width, float angleSpeed, float stepTime = 1.0f);

	//座標アクセサ
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
	int mnShakeTime = 0;
	int mnShakeTimeCount = 0;
	float mfShakeAngle = 0.0f;
	float mfShakeTimeCounter = 0.0f;
	float mfShakeTime = 0.0f;
	float mfShakeWidth = 0.0f;
	float mfShakeAngleSpeed = 0.0f;
	float mfStepTime = 0.0f;
	VECTOR mvShakePosition = VGet(0.0f,0.0f,0.0f);

};