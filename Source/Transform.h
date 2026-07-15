#pragma once
#include "Component.h"
#include "Vector3.h"

// GameObjectの位置・回転・拡大縮小を管理する
class Transform : public Component
{
public:
	Transform() = default;
	virtual ~Transform() = default;

	void SetPosition(const Vector3& _position) { mvPosition = _position; }
	const Vector3& GetPosition() const{ return mvPosition; }

	void SetRotation(const Vector3& _position) { mvRotation = _position; }
	const Vector3& GetRotation() const { return mvRotation; }

	void SetScale(const Vector3& _position) { mvScale = _position; }
	const Vector3& GetScale() const { return mvScale; }
private:
	Vector3 mvPosition;
	Vector3 mvRotation;
	Vector3 mvScale = { 1.0f, 1.0f, 1.0f };
};