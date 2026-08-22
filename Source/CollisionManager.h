#pragma once
#include <vector>

class Collider;

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	void Finalize();

	void Register(Collider* _collider);
	void Unregister(Collider* _collider);

	void Update();

	bool CheckCollision(Collider* _a, Collider* _b) const;

private:
	std::vector<Collider*> mColliders;	// 使用されている当たり判定データのコンテナ
};