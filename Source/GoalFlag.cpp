#include "GoalFlag.h"

#include "Transform.h"
#include "ModelRenderer.h"
#include "BoxCollider.h"

#include "SceneManager.h"
#include "Scene.h"

void GoalFlag::Init() {
	GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 500.0f));

	SetTag("Goal");

	auto* collider = GetComponent<BoxCollider>();
	collider->Initialize();
	collider->SetHalfSize(Vector3(10.0f, 200.0f, 10.0f));
	collider->SetOffset(Vector3(0.0f, 200.0f, 0.0f));
}

void GoalFlag::InitComponent() {
	AddComponent<Transform>();
	AddComponent<ModelRenderer>(GetModelFilename());
	AddComponent<BoxCollider>();
}

void GoalFlag::Finalize() {

}

void GoalFlag::Update(float _deltaTime) {
	GameObject::Update(_deltaTime);

	ResolvePlayerCollision();
}

void GoalFlag::Draw() {
	GameObject::Draw();
}

void GoalFlag::ResolvePlayerCollision() {
	auto* collisionManager =
		SceneManager::GetInstance()
		.GetCurrentScene()
		->GetCollisionManager();

	auto* collider =
		GetComponent<BoxCollider>();

	auto* player =
		collider->GetCollision("Player");

	if (player == nullptr) {
		return;
	}

	auto* playerCollider =
		player->GetComponent<BoxCollider>();

	if (playerCollider == nullptr) {
		return;
	}

	if (collider->GetCollision("Player")) {
		SceneManager::GetInstance().SetNextScene(SCENE_TYPE::SCENE_RESULT);
	}
}