#include "Scene.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

Scene::Scene()
	: mpObjectManager(std::make_unique<ObjectManager>())
	, mpCollisionManager(std::make_unique<CollisionManager>()) {
}

Scene::~Scene() {}

void Scene::Initialize() {

}

void Scene::Finalize() {
	mpCollisionManager->Finalize();
}

//XVˆ—
void Scene::Update(float _deltaTime) {
	mpObjectManager->Update(_deltaTime);
	mpCollisionManager->Update();
}

//•`‰æˆ—
void Scene::Draw() {
	mpObjectManager->Draw();
}






