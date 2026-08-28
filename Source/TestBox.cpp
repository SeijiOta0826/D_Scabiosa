#include "TestBox.h"

#include "Transform.h"
#include "ModelRenderer.h"
#include "Animator.h"
#include "BoxCollider.h"

#include "Debag.h"

void TestBox::Init() {
	SetTag("Wall");

	auto* collider = GetComponent<BoxCollider>();
	collider->Initialize();
	collider->SetHalfSize(Vector3(500.0f, 500.0f, 500.0f));
	collider->SetOffset(Vector3(0.0f, 500.0f, 0.0f));
}

void TestBox::InitComponent() {
	AddComponent<Transform>();
	AddComponent<ModelRenderer>(GetModelFilename());
	AddComponent<Animator>();
	AddComponent<BoxCollider>();
}

void TestBox::Finalize() {

}

void TestBox::Update(float _deltaTime) {
	GameObject::Update(_deltaTime);
}

void TestBox::Draw() {
	GameObject::Draw();

	Debag::Log("BOX当たり判定 : ", this->GetComponent<BoxCollider>()->GetCollision("Player"));
}

