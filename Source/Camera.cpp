#include "Camera.h"

#include <DxLib.h>
#include <algorithm>

#include "GameObject.h"
#include "Transform.h"
namespace {
	constexpr float MIN_VERTICAL_ANGLE = -80.0f;
	constexpr float MAX_VERTICAL_ANGLE = 80.0f;
}

Camera& Camera::GetInstance() {
	static Camera instance;
	return instance;
}

void Camera::Initialize() {
	SetCameraNearFar(100.0f, 50000.0f);	// カメラ設定
	SetBackgroundColor(200, 200, 200);	// 描画設定

	mController.SetCamera(this);

	mvWorldUp = Vector3(0.0f, 1.0f, 0.0f);
	// 演出用状態の初期化など...
}

void Camera::Finalize() {
	mpTarget = nullptr;

	// 他終了処理...
}

void Camera::Update(float _deltaTime) {
	mController.Update();

	UpdateRotation();
	UpdateTarget();
	//UpdateShake();
	UpdatePosition();
	Apply();
}

void Camera::AddRotation(
	float _horizontal, float _vertical
) {
	mfHorizontalAngle += _horizontal * mfRotationSpeed;
	mfVerticalAngle += _vertical * mfRotationSpeed;

	mfVerticalAngle =
		std::clamp(
			mfVerticalAngle,
			MIN_VERTICAL_ANGLE,
			MAX_VERTICAL_ANGLE
		);
}

void Camera::UpdateRotation() {
	// 現在設定されている回転値に基づいてカメラの回転状態を更新する
	const float horazontal =
		mfHorizontalAngle * DX_PI_F / 180.0f;

	const float vertical =
		mfVerticalAngle * DX_PI_F / 180.0f;

	mvForward = Vector3(
		sinf(horazontal) * cosf(vertical),
		sinf(vertical),
		cosf(horazontal) * cosf(vertical)
	);

	mvForward = mvForward.Normalize();

	mvRight =
		mvWorldUp.Cross(mvForward);
}

void Camera::UpdatePosition() {
	// 注視点を更新
	mvLookAtPosition =
		mvTargetPosition +
		Vector3(0.0f, mfLookAtHeight, 0.0f);

	// 注視点から距離分だけ後ろへ配置
	mvPosition =
		mvLookAtPosition - 
		GetForward() * mfDistance;
}

void Camera::UpdateTarget() {
	if (mpTarget == nullptr) return;
	
	mvTargetPosition =
		mpTarget->GetComponent<Transform>()->GetPosition();
}

void Camera::Apply() {
	SetCameraPositionAndTarget_UpVecY(
		mvPosition.ToDxVector(),
		mvLookAtPosition.ToDxVector()
	);
}

Vector3 Camera::GetForward() const {
	// Todo : カメラの向いている方向の取得
	return mvForward;
}

Vector3 Camera::GetRight() const {
	// Todo : カメラの向いている方向の取得
	return mvRight;
}

Vector3 Camera::GetUp() const {
	// Todo : カメラの上方向の取得
	return mvWorldUp;
}
