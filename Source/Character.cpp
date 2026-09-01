#include "Character.h"

#include "Transform.h"
#include "ModelRenderer.h"
#include "Animator.h"

void Character::Init() {
	// Character共通の初期化は現状なし
}

void Character::InitComponent() {
	AddComponent<Transform>();
	AddComponent<ModelRenderer>(GetModelFilename());
	auto animator = AddComponent<Animator>();
	animator->Initialize();
}

void Character::Finalize() {

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

	transform->SetPosition(newPosition);
}

void Character::UpdateMovePower(const Vector2& _move, bool _isRunning) {
	bool bIsMove = _move.Length() != 0.0f;	//移動中であるかどうかを示す

	//-- 入力状態によって目標速度を変更 --//
	if (!bIsMove) {
		mfTargetSpeed = 0.0f;
	}

	else if (_isRunning) {
		mfTargetSpeed = GetRunSpeed();
	}

	else {
		mfTargetSpeed = GetWalkSpeed();
	}

	//「目標速度」へ徐々に「現在の速度」を追いつかせる
	mfCurrentSpeed +=
		(mfTargetSpeed - mfCurrentSpeed) * 0.1f;
}

void Character::RotateTo(
	const Vector3& _direction
) {
	// Todo : Moveに応じた回転処理
	auto* transform = GetComponent<Transform>();

	const float angle = atan2f(
		_direction.x,
		_direction.z
	);

	// モデルの正面方向がゲーム内の正面と180°ずれているため補正
	transform->SetRotation(
		Vector3(
			0.0f,
			angle + DX_PI_F,
			0.0f
		)
	);
}