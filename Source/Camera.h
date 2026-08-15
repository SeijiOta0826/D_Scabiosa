#pragma once
#include "Vector3.h"
#include "CameraController.h"
class GameObject;

enum class CameraMode {
	Follow,
	Free,
	Move,
};
class Camera
{
public:
	Camera() = default;
	~Camera() = default;

	static Camera& GetInstance();

	void Initialize();
	void Finalize();
	void Update(float _deltaTime);

	// 基本情報
	Vector3 GetPosition() const;
	Vector3 GetForward() const;
	Vector3 GetRight() const;
	Vector3 GetUp() const;

	// ターゲット設定
	void SetTarget(GameObject* _target) { mpTarget = _target; }
	GameObject* GetTarget() const { return mpTarget; }
	void ClearTarget() { mpTarget = nullptr; }

	// 回転
	// Memo : CameraControllerで使用
	void AddRotation(float _horizontal, float _vertical);

	// 通常カメラ
	void SetDistance(float _distance) { mfDistance = _distance; }
	void SetLookAtHeight(float _height) { mfLookAtHeight = _height; }

	// 演出
	void StartShake(
		float _time,
		float _width,
		float _angleSpeed
	);

	void MoveTo(
		const Vector3& _position,
		const Vector3& _lookAt,
		float _duration
	);

	void Wait(float _duration);

	void FollowTarget();

private:
	void UpdatePosition();
	void UpdateRotation();
	void UpdateTarget();
	//void UpdateShake();
	void Apply();

private:
	GameObject* mpTarget = nullptr;

	CameraController mController;

	Vector3 mvPosition;
	Vector3 mvLookAtPosition;

	Vector3 mvForward;
	Vector3 mvRight;
	Vector3 mvWorldUp;

	Vector3 mvTargetPosition;

	float mfHorizontalAngle;
	float mfVerticalAngle;
	float mfDistance = 200.0f;
	float mfLookAtHeight = 80.0f;

	float mfRotationSpeed = 1.0f;
};