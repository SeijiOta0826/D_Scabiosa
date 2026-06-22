#pragma once
#include "DxLib.h"
#include "Vector3.h"

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
	Vector3 GetPosition() { return mvPosition; }
	void SetPosition(Vector3 _pos) { mvPosition = _pos; }

	Vector3 GetLookAtPosition() { return mvLookAtPosition; }	//注視点取得

private:
	
	float mfHorizontalAngle;	//水平方向アングル
	float mfVerticalAngle;		//垂直方向アングル

	Vector3 mvPosition;			//カメラ座標
	Vector3 mvLookAtPosition;	//カメラの注視点座標

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
	Vector3 mvShakePosition;

};