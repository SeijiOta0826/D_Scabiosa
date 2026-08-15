#include "PlayerController.h"

#include "Player.h"
#include "Character.h"

#include "Camera.h"

#include "InputManager.h"
#include "Vector3.h"
#include "Vector2.h"

void PlayerController::Init(
	Player* _player
) {
	mpPlayer = _player;
}

void PlayerController::Update(float _deltaTime) {
	UpdateMove(_deltaTime);
	UpdateAttack();
	// UpdateJump();
}

void PlayerController::UpdateMove(float _deltaTime) {
	Vector2 direction;

	direction.x += InputManager::GetInstance().GetAxis(Axis::MoveX);
	direction.y += InputManager::GetInstance().GetAxis(Axis::MoveY);

	if (direction.Length() <= 0.0f) {
		return;
	}

	Vector3 forward = Camera::GetInstance().GetForward();
	forward.y = 0.0f;
	forward = forward.Normalize();

	Vector3 right = Camera::GetInstance().GetRight();
	right.y = 0.0f;
	right = right.Normalize();

	Vector3 moveDirection =
		right * direction.x +
		forward * direction.y;

	moveDirection = moveDirection.Normalize();

	mpPlayer->Move(moveDirection, _deltaTime);
	mpPlayer->RotateTo(moveDirection);
}

void PlayerController::UpdateAttack() {
	if (InputManager::GetInstance().GetButtonDown(Button::Attack)) {
		mpPlayer->Attack();
	}
}