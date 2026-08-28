#include "CollisionManager.h"

#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "GameObject.h"

#include <DxLib.h>	// デバッグ表示のカラー指定のため使用
#include <cmath>
#include <algorithm>

#include "Debag.h"

void CollisionManager::Initialize() {

}

void CollisionManager::Finalize() {
	for (auto* collider : mColliders){
		collider->ClearCollisions();
	}

	mColliders.clear();
}

void CollisionManager::Update() {
	// 前フレームの衝突結果をリセット
	for (auto* collider : mColliders) {
		collider->ClearCollisions();
	}

	// 判定を行うColliderを選び、衝突結果を各自処理するコンテナに登録
	for (size_t i = 0;
		i < mColliders.size();
		++i) {
		Collider* a = mColliders[i];
		
		if (!a->IsEnabled()) continue;

		for (size_t j = i + 1;
			j < mColliders.size();
			++j) {
			Collider* b = mColliders[j];

			if (!b->IsEnabled()) continue;

			if (CheckCollision(a, b)) {
				a->AddCollision(b);
				b->AddCollision(a);
			}
		}
	}
}

bool CollisionManager::CheckCollision(
	Collider* _a, Collider* _b
) const {
	// Todo : 各Shape同士の計算処理に流す
	const Shape TypeA = _a->GetShapeType();
	const Shape TypeB = _b->GetShapeType();

	if (Shape::Sphere == TypeA) {
		auto* sphereColliderA = static_cast<SphereCollider*>(_a);

		if (Shape::Sphere == TypeB) {
			auto* sphereColliderB = static_cast<SphereCollider*>(_b);
			return CheckSphereSphere(sphereColliderA, sphereColliderB);
		}

		if (Shape::Box == TypeB) {
			auto* sphereColliderB = static_cast<BoxCollider*>(_b);
			return CheckSphereBox(sphereColliderA, sphereColliderB);
		}
	}

	if (Shape::Box == TypeA) {
		auto* sphereColliderA = static_cast<BoxCollider*>(_a);

		if (Shape::Sphere == TypeB) {
			auto* sphereColliderB = static_cast<SphereCollider*>(_b);
			return CheckSphereBox(sphereColliderB, sphereColliderA);
		}

		if (Shape::Box == TypeB) {
			auto* sphereColliderB = static_cast<BoxCollider*>(_b);
			return CheckBoxBox(sphereColliderA, sphereColliderB);
		}
	}
}

void CollisionManager::Register(
	Collider* _collider
) {
	if (_collider == nullptr) return;

	for (auto* collider : mColliders) {
		if (collider == _collider) return;
	}

	mColliders.push_back(_collider);
}

void CollisionManager::Unregister(
	Collider* _collider
) {
	for (auto collider = mColliders.begin();
		collider != mColliders.end();
		++collider) {
		if (*collider == _collider) {
			mColliders.erase(collider);
			return;
		}
	}
}

void CollisionManager::DrawDebag() const{
	for (auto* collider : mColliders) {
		if (!collider->IsEnabled())
			continue;

		auto boxCollider = static_cast<BoxCollider*>(collider);
		const int color =
			boxCollider->IsColliding()
			? GetColor(255, 0, 0)
			: GetColor(0, 255, 0);

		Debag::DrawDebugBox(
			boxCollider->GetWorldPosition(),
			boxCollider->GetHalfSize(),
			color
		);
	}
}

bool CollisionManager::CheckSphereSphere(
	SphereCollider* _sphereA,
	SphereCollider* _sphereB
) const {
	const Vector3 posA = _sphereA->GetWorldPosition();
	const Vector3 posB = _sphereB->GetWorldPosition();

	const float radiusA = _sphereA->GetRadius();
	const float radiusB = _sphereB->GetRadius();

	const Vector3 difference = posB - posA;

	const float distanceSquared = difference.Length();

	const float radiusSum = radiusA + radiusB;

	return distanceSquared <= radiusSum * radiusSum;
}

bool CollisionManager::CheckSphereBox(
	SphereCollider* _sphereA, 
	BoxCollider* _boxB
) const {
	const Vector3 sphereCenter =
		_sphereA->GetWorldPosition();

	const float sphereRadius =
		_sphereA->GetRadius();

	const Vector3 boxCenter =
		_boxB->GetWorldPosition();

	const Vector3 halfSize =
		_boxB->GetHalfSize();

	// Boxの最小・最大座標
	const Vector3 boxMin =
		boxCenter - halfSize;

	const Vector3 boxMax =
		boxCenter + halfSize;

	// Sphereの中心からBox上の最近接点を求める
	const float closestX =
		std::clamp(sphereCenter.x, boxMin.x, boxMax.x);

	const float closestY =
		std::clamp(sphereCenter.y, boxMin.y, boxMax.y);

	const float closestZ =
		std::clamp(sphereCenter.z, boxMin.z, boxMax.z);

	const Vector3 closestPoint(
		closestX,
		closestY,
		closestZ
	);

	// Sphereの中心と最近接点の距離
	const Vector3 difference =
		closestPoint - sphereCenter;

	const float distanceSquared = difference.Length();

	return distanceSquared <=
		sphereRadius * sphereRadius;
}

bool CollisionManager::CheckBoxBox(
	BoxCollider* _boxA,
	BoxCollider* _boxB
) const {
	const Vector3 posA =
		_boxA->GetWorldPosition();

	const Vector3 posB =
		_boxB->GetWorldPosition();

	const Vector3 halfA =
		_boxA->GetHalfSize();

	const Vector3 halfB =
		_boxB->GetHalfSize();

	const Vector3 minA =
		posA - halfA;

	const Vector3 maxA =
		posA + halfA;

	const Vector3 minB =
		posB - halfB;

	const Vector3 maxB =
		posB + halfB;

	if (maxA.x < minB.x ||
		minA.x > maxB.x)
	{
		return false;
	}

	if (maxA.y < minB.y ||
		minA.y > maxB.y)
	{
		return false;
	}

	if (maxA.z < minB.z ||
		minA.z > maxB.z)
	{
		return false;
	}

	return true;
}

bool CollisionManager::GetBoxBoxCollision(
	BoxCollider* _a,
	BoxCollider* _b,
	CollisionInfo& _info
) const
{
	if (_a == nullptr || _b == nullptr) 
		return false;

	const Vector3 posA = _a->GetWorldPosition();
	const Vector3 posB = _b->GetWorldPosition();

	const Vector3 halfA = _a->GetHalfSize();
	const Vector3 halfB = _b->GetHalfSize();

	const float overlapX =
		(halfA.x + halfB.x) -
		std::abs(posA.x - posB.x);

	const float overlapY =
		(halfA.y + halfB.y) -
		std::abs(posA.y - posB.y);

	const float overlapZ =
		(halfA.z + halfB.z) -
		std::abs(posA.z - posB.z);

	// そもそも衝突していない
	if (overlapX <= 0.0f ||
		overlapY <= 0.0f ||
		overlapZ <= 0.0f)
	{
		return false;
	}

	// 一番めり込みが浅い軸を選択
	_info.penetration = overlapX;
	_info.normal = Vector3(
		posA.x < posB.x ? -1.0f : 1.0f,
		0.0f,
		0.0f
	);

	if (overlapY < _info.penetration)
	{
		_info.penetration = overlapY;

		_info.normal = Vector3(
			0.0f,
			posA.y < posB.y ? -1.0f : 1.0f,
			0.0f
		);
	}

	if (overlapZ < _info.penetration)
	{
		_info.penetration = overlapZ;

		_info.normal = Vector3(
			0.0f,
			0.0f,
			posA.z < posB.z ? -1.0f : 1.0f
		);
	}

	return true;
}