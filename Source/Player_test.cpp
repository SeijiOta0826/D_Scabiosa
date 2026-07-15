#include "Player_test.h"

#include "Transform.h"
#include "ModelRenderer.h"
#include "Animator.h"

void Player_test::Init() {

}

void Player_test::InitComponent() {
	AddComponent<Transform>();
	AddComponent<ModelRenderer>("Resource/3D/Paladin/Mesh.mv1");
	AddComponent<Animator>();
}

void Player_test::Update() {
	GameObject::Update();
}

void Player_test::Draw() {
	GameObject::Draw();
}