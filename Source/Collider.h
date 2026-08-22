#pragma once
#include "Component.h"
#include "Vector3.h"

#include <string>
#include <vector>

class GameObject;
class CollisionManager;

class Collider : public Component
{
public:
	Collider() = default;
	~Collider();

	void Init() override;

	void SetRadius(float _radius) { mfRadius = _radius; }
	float GetRadius() const { return mfRadius; }

	void SetOffset(const Vector3& _offset) { mvOffSetPos = _offset; }
	const Vector3& GetOffset() const { return mvOffSetPos; }

	Vector3 GetWorldPosition() const;

	bool IsColliding() const;	// 何かしらに当たったら反応
	bool IsColliding(const std::string& _tag) const;

	GameObject* GetCollision(const std::string& _tag) const;

private:
	friend class CollisionManager;

	void AddCollision(Collider* _collider) { mCollisions.push_back(_collider); }
	void ClearCollisions() { mCollisions.clear(); }

private:
	float mfRadius = 1.0f;
	Vector3 mvOffSetPos;

	std::vector<Collider*> mCollisions;
};