#pragma once

class Camera;

class CameraController
{
public:
	CameraController() = default;
	~CameraController() = default;

	void Update();

	void SetCamera(Camera* _camera) { mpCamera = _camera; }

private:
	Camera* mpCamera = nullptr;
};