#include "Player.h"

#include "Transform.h"
#include "ModelRenderer.h"
#include "Animator.h"

#include "BoxCollider.h"
#include "Collider.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Camera.h"
#include "InputManager.h"

#include "PlayerController.h"
#include "Debag.h"

void Player::Init() {
	Character::Init();
	mController.Init(this);

	SetTag("Player");

	auto* collider = GetComponent<BoxCollider>();
	collider->Initialize();
	collider->SetHalfSize(Vector3(10.0f, 30.0f, 10.0f));
	collider->SetOffset(Vector3(0.0f, 50.0f, 0.0f));
}

void Player::InitComponent() {
	Character::InitComponent();
	AddComponent<BoxCollider>();
}

void Player::Update(float _deltaTime) {
	mController.Update(_deltaTime);
	UpdateAnimation();

	ResolveWallCollision();

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

void Player::ResolveWallCollision() {
	auto* collisionManager =
		SceneManager::GetInstance()
		.GetCurrentScene()
		->GetCollisionManager();

	auto* collider =
		GetComponent<BoxCollider>();

	auto* wall =
		collider->GetCollision("Wall");

	if (wall == nullptr) {
		return;
	}

	auto* wallCollider =
		wall->GetComponent<BoxCollider>();

	if (wallCollider == nullptr) {
		return;
	}

	CollisionInfo info;

	if (!collisionManager->GetBoxBoxCollision(
		collider,
		wallCollider,
		info)) {
		return;
	}

	auto* transform =
		GetComponent<Transform>();

	Vector3 position =
		transform->GetPosition();

	position += info.normal * info.penetration;

	transform->SetPosition(position);
}