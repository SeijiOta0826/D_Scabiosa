#include "Collider.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

#include "Transform.h"

void Collider::Initialize() {
	SceneManager::GetInstance().GetCurrentScene()
		->GetCollisionManager()
		->Register(this);
}

void Collider::Finalize() {
	SceneManager::GetInstance().GetCurrentScene()
		->GetCollisionManager()
		->Unregister(this);
}

bool Collider::IsColliding() const{
	return !mCollisions.empty();
}

bool Collider::IsColliding(
	const std::string& _tag
) const {
	for (auto* collider : mCollisions) {
		if (collider->GetGameObject()->GetTag() == _tag) {
			return true;
		}
	}

	return false;
}

GameObject* Collider::GetCollision(
	const std::string& _tag
) const {
	for (auto* collider : mCollisions) {
		std::string str = collider->GetGameObject()->GetTag();
		if (str == _tag) {
			return collider->GetGameObject();
		}
	}

	return nullptr;
}

Vector3 Collider::GetWorldPosition() const {
	return
		mpGameObject
		->GetComponent<Transform>()
		->GetPosition()
		+ mvOffSetPos;
}