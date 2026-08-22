#include "Player.h"

#include "Transform.h"
#include "ModelRenderer.h"
#include "Animator.h"
#include "Collider.h"

#include "Camera.h"
#include "InputManager.h"

#include "PlayerController.h"

void Player::Init() {
	Character::Init();
	mController.Init(this);

	GetComponent<Collider>()->Init();
}

void Player::InitComponent() {
	Character::InitComponent();
	AddComponent<Collider>();
}

void Player::Update(float _deltaTime) {
	mController.Update(_deltaTime);
	UpdateAnimation();
	//Move();	//移動処理
	//RotationByMove();

	Character::Update(_deltaTime);
}

void Player::Draw() {
	Character::Draw();
}

void Player::UpdateMovePower(const Vector3& _move, bool _isRunning) {
	bool bIsMove = _move.Length() != 0.0f;	//移動中であるかどうかを示す

	//-- 入力状態によって目標速度を変更 --//
	if (!bIsMove) {
		mfTargetSpeed = 0.0f;
	}

	else if (_isRunning) {
		mfTargetSpeed = RUN_SPEED;
	}

	else {
		mfTargetSpeed = WALK_SPEED;
	}

	//「目標速度」へ徐々に「現在の速度」を追いつかせる
	mfCurrentSpeed +=
		(mfTargetSpeed - mfCurrentSpeed) * 0.1f;
}

void Player::RotationByMove() {
	float fSubAngle = mfTargetAngle - mfAngle;

	if (fSubAngle < -DX_PI_F) fSubAngle += DX_TWO_PI_F;
	if (fSubAngle > DX_PI_F) fSubAngle -= DX_TWO_PI_F;

	if (fSubAngle > 0.0f) {
		fSubAngle -= ROTATE_SPEED;
		if (fSubAngle < 0.0f) {
			fSubAngle = 0.0f;
		}
	}

	else if (fSubAngle < 0.0f) {
		fSubAngle += ROTATE_SPEED;
		if (fSubAngle > 0.0f) {
			fSubAngle = 0.0f;
		}
	}

	mfAngle = mfTargetAngle - fSubAngle;

	GetComponent<Transform>()->SetRotation(
		Vector3(
			GetComponent<Transform>()->GetRotation().x,
			mfAngle + DX_PI_F,
			GetComponent<Transform>()->GetRotation().z
		)
	);
}

const std::string& Player::DetermineAnimationState() {

	if (mfCurrentSpeed > WALK_SPEED) {
		return "Run";
	}

	if (mfCurrentSpeed > 0.05f) {
		return "Walk";
	}

	return "Idel";
}

void Player::UpdateAnimation() {
	GetComponent<Animator>()->CrossFade(DetermineAnimationState(), 2.0f);
}