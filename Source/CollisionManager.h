#pragma once
#include "Vector3.h"
#include <vector>

class Collider;
class SphereCollider;
class BoxCollider;
class CapsuleCollider;

enum class Shape
{
	Sphere,
	Box,
	Capsule,
};

struct CollisionInfo
{
	Vector3 normal;				// 押し出す方向
	float penetration = 0.0f;	// どれだけめり込んでいるか
};

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	void Initialize();
	void Finalize();

	void Register(Collider* _collider);
	void Unregister(Collider* _collider);

	void Update();

	bool CheckCollision(Collider* _a, Collider* _b) const;

	void DrawDebag() const;

	bool GetBoxBoxCollision(
		BoxCollider* _a,
		BoxCollider* _b,
		CollisionInfo& _info
	) const;

private:
	bool CheckSphereSphere(SphereCollider* _sphereA, SphereCollider* _sphereB) const;
	bool CheckSphereBox(SphereCollider* _sphereA, BoxCollider* _boxB) const;
	//bool CheckSphereCapsule(SphereCollider* _sphereA, CapsuleCollider* _capsuleB) const;

	bool CheckBoxBox(BoxCollider* _boxA, BoxCollider* _boxB) const;
	//bool CheckBoxCapsule(BoxCollider* _boxA, CapsuleCollider* _capsuleB) const;

	//bool CheckCapsuleCapsule(CapsuleCollider* _capsuleA, CapsuleCollider* _capsuleB) const;

	/*float DistancePointSegmentSquared(
		const Vector3& _point,
		const Vector3& _start,
		const Vector3& _end
	) const;

	float DistanceSegmentSegmentSquared(
		const Vector3& _startA,
		const Vector3& _endA,
		const Vector3& _startB,
		const Vector3& _endB
	) const;*/

	/*float DistanceSegmentAABBSquared(
		const Vector3& _start,
		const Vector3& _end,
		const Vector3& _boxMin,
		const Vector3& _boxMax
	) const;*/

private:
	std::vector<Collider*> mColliders;	// 使用されている当たり判定データのコンテナ
};