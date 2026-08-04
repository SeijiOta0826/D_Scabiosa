#include "Character.h"

#include "Transform.h"
#include "ModelRenderer.h"
#include "Animator.h"
//#include "Collider.h"

void Character::Init() {
	// Character共通の初期化は現状なし
}

void Character::InitComponent() {
	AddComponent<Transform>();
	AddComponent<ModelRenderer>(GetModelFilename());
	AddComponent<Animator>();

	// Todo : ColliderCoponent実装次第ここに追加
}

void Character::Update(float _deltaTime) {
	GameObject::Update(_deltaTime);

	// Character共通のUpdate処理
}

void Character::Draw() {
	GameObject::Draw();

	// Character共通のDraw処理
}

void Character::Move(
	const Vector3& _direction,
	float _deltaTime
) {
	// Todo : CharaterとしてのMove処理
	auto* transform = GetComponent<Transform>();

	const Vector3 moveAmount =
		_direction * GetSpeed() * _deltaTime;

	const Vector3 newPosition =
		transform->GetPosition() + moveAmount;

	GetComponent<Transform>()->SetPosition(newPosition);
}

void Character::Attack() {
	// Todo : CharaterとしてのAttack処理
}

void Character::TakeDamage(float _damage) {
	// Todo : CharaterとしてのTakeDamage処理
}





