#include "PlayerController.h"

#include "Player.h"
#include "Character.h"

#include "Camera.h"

#include "InputManager.h"
#include "Vector3.h"

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
	Vector3 direction;

	direction.x += InputManager::GetInstance().GetAxis(Axis::MoveX);
	direction.y += InputManager::GetInstance().GetAxis(Axis::MoveY);

	if (direction.Length() > 0.0f) {
		mpPlayer->Move(direction, _deltaTime);
	}
}

void PlayerController::UpdateAttack() {
	if (InputManager::GetInstance().GetButtonDown(Button::Attack)) {
		mpPlayer->Attack();
	}
}