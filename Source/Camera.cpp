#include "Camera.h"
#include <cmath>

#include "SceneManager.h"
#include "ObjectManager.h"
#include "Scene.h"

#include "Player_test.h"
#include "Transform.h"

#include "InputManager.h"

Camera::Camera()
	:mfHorizontalAngle(0.0f)
	, mfVerticalAngle(0.0f)
	, mvPosition()
	, mvLookAtPosition()
	, mpTarget(nullptr) {

}

Camera::~Camera() {

}

Camera& Camera::GetInstance() {
	static Camera instance;
	return instance;
}

void Camera::Initialize() {
	SetCameraNearFar(100.f, 50000.0f);	//カメラのクリッピング距離の設定
	SetBackgroundColor(200, 200, 200);	//背景色を設定(灰色)

	SetCameraPositionAndTarget_UpVecY(mvPosition.ToDxVector(), mvLookAtPosition.ToDxVector());	//カメラ座標とターゲットの座標をセット
}

void Camera::Finalize() {

}

void Camera::Update(float _deltaTime) {

	UpdateRotation();	//回転処理

	//ターゲットobjがセッティングされていない場合
	if (mpTarget == nullptr) {
/*		mpTarget = SceneManager::GetInstance().GetCurrentScene()
			->GetObjectManager()->GetObject3DByTag(Object3D::OBJ_PLAYER);	//mpTargetにプレイヤーのデータをぶち込む*/

		mpTarget = SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->FindObject<Player_test>();
	}

	//ターゲットobjがセッティングされている場合
	if (mpTarget != nullptr) {
		mvLookAtPosition = mpTarget->GetComponent<Transform>()->GetPosition();	//基本座標を対象に座標にして少し上にずらす
		mvLookAtPosition.y += 80.0f;
	}

	else {
		mvLookAtPosition.y = 80.0f;	//注視点を少し上にずらす
	}

	Shake();	// 画面揺れ処理

	{
		Vector3 temp;    // 作業用変数

		// 球面上の座標を求める
		const float distance = 500.0f;
		temp.x = distance * cosf(mfVerticalAngle / 180.0f * DX_PI_F) * sinf(mfHorizontalAngle / 180.0f * DX_PI_F);
		temp.y = distance * sinf(mfVerticalAngle / 180.0f * DX_PI_F);
		temp.z = -(distance * cosf(mfVerticalAngle / 180.0f * DX_PI_F) * cosf(mfHorizontalAngle / 180.0f * DX_PI_F));

		// 上で求めた座標に注視点の座標を足したものがカメラ座標となる
		mvPosition = temp + mvLookAtPosition;

		// 画面揺れの分を加算するように変更
		SetCameraPositionAndTarget_UpVecY(VAdd(mvPosition.ToDxVector(), mvShakePosition.ToDxVector()), VAdd(mvLookAtPosition.ToDxVector(), mvShakePosition.ToDxVector()));

	}
}

//回転処理
void Camera::UpdateRotation() {
	float fCameraSensitivity = 5.0f;	//カメラ感度
	float fCameraMaxPitch = 80.0f;


	//方向キーでカメラ操作
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		mfHorizontalAngle += fCameraSensitivity;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		mfHorizontalAngle -= fCameraSensitivity;
	}

	if (CheckHitKey(KEY_INPUT_UP)) {
		mfVerticalAngle += fCameraSensitivity;
	}

	if (CheckHitKey(KEY_INPUT_DOWN)) {
		mfVerticalAngle -= fCameraSensitivity;
	}

	Stick pStick = InputManager::GetStickInfo().Right;	//右スティックのい情報取得

	if (pStick.x < 0.0f) {
		mfHorizontalAngle += fCameraSensitivity * pStick.length;
	}
	else if (pStick.x > 0.0f) {
		mfHorizontalAngle -= fCameraSensitivity * pStick.length;
	}

	if (pStick.y < 0.0f) {
		mfVerticalAngle += fCameraSensitivity * pStick.length;
	}
	else if (pStick.y > 0.0f) {
		mfVerticalAngle -= fCameraSensitivity * pStick.length;
	}

	if (mfHorizontalAngle >= 180.0f)
	{
		mfHorizontalAngle -= 360.0f;
	}

	if (mfHorizontalAngle <= -180.0f)
	{
		mfHorizontalAngle += 360.0f;
	}

	if (mfVerticalAngle >= fCameraMaxPitch)
	{
		mfVerticalAngle = fCameraMaxPitch;
	}

	if (mfVerticalAngle <= -fCameraMaxPitch)
	{
		mfVerticalAngle = -fCameraMaxPitch;
	}

}

// 画面揺れ
void Camera::Shake() {
	if (mfShakeTimeCounter < mfShakeTime) {
		// sinf を利用して揺らし座標を算出
		// note: 一旦Y座標だけを揺らしてみる
		mvShakePosition.y = sinf(mfShakeAngle) * (1.0f - (mfShakeTimeCounter / mfShakeTime)) * mfShakeWidth;
		mvShakePosition.x = 0.0f;
		mvShakePosition.z = 0.0f;

		// 揺らし処理に使用する sinf に渡す角度の変更処理
		mfShakeAngle += mfShakeAngleSpeed * mfStepTime;

		// 揺らす時間を経過させる
		mfShakeTimeCounter += mfStepTime;
	}
	else {
		// 揺らされていない場合は揺らし処理による加算座標を０にする
		mvShakePosition *= 0.0f;
	}
}

// 画面揺れ設定
void Camera::SetupShake(float time, float width, float angleSpeed, float stepTime) {
	mfShakeTimeCounter = 0.0f;
	mfShakeTime = time;
	mfShakeWidth = width;
	mfShakeAngleSpeed = angleSpeed;
	mfStepTime = stepTime;
}

