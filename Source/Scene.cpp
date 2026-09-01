#include "Scene.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

Scene::Scene()
	: mpObjectManager(std::make_unique<ObjectManager>())
	, mpCollisionManager(std::make_unique<CollisionManager>()) {
}

Scene::~Scene() {}

void Scene::Initialize() {
	mpObjectManager->Initialize();
	mpCollisionManager->Initialize();
}

void Scene::Finalize() {
	mpObjectManager->Finalize();
	mpCollisionManager->Finalize();
}

//更新処理
void Scene::Update(float _deltaTime) {
	mpCollisionManager->Update();
	mpObjectManager->Update(_deltaTime);
}

//描画処理
void Scene::Draw() {
	mpObjectManager->Draw();
	//mpCollisionManager->DrawDebag();	// Colliderの形のデバック用描画処理
}






