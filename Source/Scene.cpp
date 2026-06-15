#include"Scene.h"
#include "ObjectManager.h"

Scene::Scene() 
	: mpObjectManager(std::make_unique<ObjectManager>()) {
}

//XVˆ—
void Scene::Update(float _deltaTime) {
	mpObjectManager->Update(_deltaTime);
}

//•`‰æˆ—
void Scene::Draw() {
	mpObjectManager->Draw();
}






