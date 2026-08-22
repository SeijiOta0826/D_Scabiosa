#include "TestBox.h"

#include "Transform.h"
#include "ModelRenderer.h"
#include "Animator.h"
#include "Collider.h"

#include "Debag.h"

void TestBox::Init() {
	auto* collider = GetComponent<Collider>();
	collider->Init();
	collider->SetRadius(500.0f);
	collider->SetOffset(Vector3(0.0f, 500.0f, 0.0f));
}

void TestBox::InitComponent() {
	AddComponent<Transform>();
	AddComponent<ModelRenderer>(GetModelFilename());
	AddComponent<Animator>();
	AddComponent<Collider>();
}

void TestBox::Update(float _deltaTime) {
	GameObject::Update(_deltaTime);
}

void TestBox::Draw() {
	GameObject::Draw();

	Debag::Log("BOX当たり判定 : ", this->GetComponent<Collider>()->GetCollision("Player"));
}

