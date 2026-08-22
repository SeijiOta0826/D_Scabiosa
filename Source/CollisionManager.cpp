#include "CollisionManager.h"

#include "Collider.h"
#include "GameObject.h"

#include <cmath>

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
	// Todo : 衝突を判定する計算処理

	Vector3 difference =
		_a->GetWorldPosition() -
		_b->GetWorldPosition();

	const float distance = difference.Length();

	const float radiusSum =
		_a->GetRadius() +
		_b->GetRadius();

	return distance <= radiusSum;
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