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
#include "Debag.h"

void Player::Init() {
	Character::Init();
	mController.Init(this);

	SetTag("Player");

	auto* collider = GetComponent<BoxCollider>();
	collider->Initialize();
	collider->SetHalfSize(Vector3(25.0f, 100.0f, 25.0f));
	collider->SetOffset(Vector3(0.0f, 100.0f, 0.0f));
}

void Player::InitComponent() {
	Character::InitComponent();
	AddComponent<BoxCollider>();

	auto animator = GetComponent<Animator>();

	animator->AddAnimation("Idle", "Resource/3D/Character/Paladin/Idle.mv1");
	animator->AddAnimation("Walk", "Resource/3D/Character/Paladin/Walking.mv1");
	animator->AddAnimation("Run", "Resource/3D/Character/Paladin/Running.mv1");
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

std::string Player::DetermineAnimationState() {

	if (GetSpeed() > GetWalkSpeed() + 100.0f) {
		return "Run";
	}

	if (GetSpeed() > 10.0f) {
		return "Walk";
	}

	return "Idle";
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