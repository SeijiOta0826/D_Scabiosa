#include "GameObject.h"
#include "Component.h"

void GameObject::Initialize(ObjectManager* _manager) {
	//mpObjectManager = _manager;
	this->Init();
}
void GameObject::Update() {
	for (auto& component : mComponents) {
		component->Update();
	}
}
 
void GameObject::Draw() {
	for (auto& component : mComponents) {
		component->Draw();
	}
}