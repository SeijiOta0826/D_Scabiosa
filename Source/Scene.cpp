#include"Scene.h"
#include "ObjectManager.h"

Scene::Scene() {
	mpObjectManager = new ObjectManager();
}

Scene::~Scene() {
	if (mpObjectManager != nullptr) {
		delete mpObjectManager;
	}
}

//XVˆ—
void Scene::Update(float _deltaTime) {
	if (mpObjectManager != nullptr) {
		mpObjectManager->Update(_deltaTime);
	}
}

//•`‰æˆ—
void Scene::Draw() {
	if (mpObjectManager != nullptr) {
		mpObjectManager->Draw();
	}
}






