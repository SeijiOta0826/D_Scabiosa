#include "GameObject.h"
#include "Component.h"

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