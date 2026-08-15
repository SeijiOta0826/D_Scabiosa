#include "CameraController.h"

#include "InputManager.h"
#include "Camera.h"
void CameraController::Update() {
	if (mpCamera == nullptr) return;

	float horizontal = InputManager::GetInstance().GetAxis(Axis::LookX);
	float vertical = InputManager::GetInstance().GetAxis(Axis::LookY);

	mpCamera->AddRotation(horizontal, vertical);
}