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
	UpdateDash();
}

void PlayerController::UpdateMove(float _deltaTime) {
	Vector2 inputDirection;

	inputDirection.x += InputManager::GetInstance().GetAxis(Axis::MoveX);
	inputDirection.y += InputManager::GetInstance().GetAxis(Axis::MoveY);

	mpPlayer->UpdateMovePower(
		inputDirection,
		mpPlayer->GetIsRunning()
	);

	// 入力がある場合だけ移動方向を更新
	if (inputDirection.Length() > 0.0f) {
		Vector3 forward = Camera::GetInstance().GetForward();
		forward.y = 0.0f;
		forward = forward.Normalize();

		Vector3 right = Camera::GetInstance().GetRight();
		right.y = 0.0f;
		right = right.Normalize();

		mvMoveDirection =
			right * inputDirection.x +
			forward * inputDirection.y;

		mvMoveDirection = mvMoveDirection.Normalize();

		mpPlayer->RotateTo(mvMoveDirection);
	}

	// 入力がなくても、保持している方向に移動する
	mpPlayer->Move(mvMoveDirection, _deltaTime);
}

void PlayerController::UpdateAttack() {

}

void PlayerController::UpdateDash() {
	mpPlayer->SetIsRunning(InputManager::GetInstance().GetButton(Button::Dash));
}

