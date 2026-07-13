#include "GameObject.h"
#include "Component.h"

void GameObject::Initialize(ObjectManager_test* _manager) {
	mpObjectManager = _manager;
	this->Init();			// 継承先特有の初期化処理
	this->InitComponent();	// 継承先が持つコンポーネント初期設定
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