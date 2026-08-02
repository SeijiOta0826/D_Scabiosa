#include "Player.h"

#include "Transform.h"
#include "ModelRenderer.h"
#include "Animator.h"

#include "Camera.h"
#include "InputManager.h"


void Player::Init() {

}

void Player::InitComponent() {
	AddComponent<Transform>();
	AddComponent<ModelRenderer>("Resource/3D/Paladin/Mesh.mv1");
	AddComponent<Animator>();
}

void Player::Update() {
	UpdateAnimation();
	Move();	//移動処理
	RotationByMove();

	GameObject::Update();
}

void Player::Draw() {
	GameObject::Draw();
}

void Player::Move() {
	Vector3 vMoveVec;	//移動方向
	bool bIsRunning = false;

	Vector3 vUpMoveVector;				//カメラの前方向ベクトル(奥)
	Vector3 vLeftMoveVector;			//カメラの左方向ベクトル
	Vector3 vWorldUp(0.0f, 1.0f, 0.0f);	//ワールド座標の上向きベクトル(左方向算出時使用)

	{
		//カメラから見た奥方向を取得
		vUpMoveVector =
			Camera::GetInstance().GetLookAtPosition() - Camera::GetInstance().GetPosition();
		vUpMoveVector.y = 0.0f;

		//カメラから見た左方向を取得
		vLeftMoveVector =
			vUpMoveVector.Cross(vWorldUp);
		vLeftMoveVector.y = 0.0f;

		//正規化
		vUpMoveVector = vUpMoveVector.Normalize();
		vLeftMoveVector = vLeftMoveVector.Normalize();
	}

	/*if (InputManager::GetInstance().CheckPressKey(KEY_INPUT_W)) vMoveVec = vMoveVec + vUpMoveVector;
	if (InputManager::GetInstance().CheckPressKey(KEY_INPUT_A)) vMoveVec = vMoveVec + vLeftMoveVector;
	if (InputManager::GetInstance().CheckPressKey(KEY_INPUT_S)) vMoveVec = vMoveVec + (vUpMoveVector * -1.0f);
	if (InputManager::GetInstance().CheckPressKey(KEY_INPUT_D)) vMoveVec = vMoveVec + (vLeftMoveVector * -1.0f);*/

	/*if (InputManager_test::GetInstance().GetButton(KEY_INPUT_A)) vMoveVec = vMoveVec + vLeftMoveVector;
	if (InputManager_test::GetInstance().GetButton(KEY_INPUT_S)) vMoveVec = vMoveVec + (vUpMoveVector * -1.0f);
	if (InputManager_test::GetInstance().GetButton(KEY_INPUT_D)) vMoveVec = vMoveVec + (vLeftMoveVector * -1.0f);*/
	if (vMoveVec.x != 0.0f || vMoveVec.z != 0.0f) {
		vMoveVec = vMoveVec.Normalize();
		mfTargetAngle = atan2f(vMoveVec.x, vMoveVec.z);
	}

	if (InputManager::GetInstance().GetButton(Button::Dash)) bIsRunning = true;
	UpdateMovePower(vMoveVec, bIsRunning);

	GetComponent<Transform>()->SetPosition(
		GetComponent<Transform>()->GetPosition() + vMoveVec * mfCurrentSpeed);
}

void Player::UpdateMovePower(const Vector3& _move, bool _isRunning) {
	bool bIsMove = _move.Length() != 0.0f;	//移動中であるかどうかを示す

	//-- 入力状態によって目標速度を変更 --//
	if (!bIsMove) {
		mfTargetSpeed = 0.0f;
	}

	else if (_isRunning) {
		mfTargetSpeed = RUN_SPEED;
	}

	else {
		mfTargetSpeed = WALK_SPEED;
	}

	//「目標速度」へ徐々に「現在の速度」を追いつかせる
	mfCurrentSpeed +=
		(mfTargetSpeed - mfCurrentSpeed) * 0.1f;
}

void Player::RotationByMove() {
	float fSubAngle = mfTargetAngle - mfAngle;

	if (fSubAngle < -DX_PI_F) fSubAngle += DX_TWO_PI_F;
	if (fSubAngle > DX_PI_F) fSubAngle -= DX_TWO_PI_F;

	if (fSubAngle > 0.0f) {
		fSubAngle -= ROTATE_SPEED;
		if (fSubAngle < 0.0f) {
			fSubAngle = 0.0f;
		}
	}

	else if (fSubAngle < 0.0f) {
		fSubAngle += ROTATE_SPEED;
		if (fSubAngle > 0.0f) {
			fSubAngle = 0.0f;
		}
	}

	mfAngle = mfTargetAngle - fSubAngle;

	GetComponent<Transform>()->SetRotation(
		Vector3(
			GetComponent<Transform>()->GetRotation().x,
			mfAngle + DX_PI_F,
			GetComponent<Transform>()->GetRotation().z
		)
	);
}

const std::string& Player::DetermineAnimationState() {

	if (mfCurrentSpeed > WALK_SPEED) {
		return "Run";
	}

	if (mfCurrentSpeed > 0.05f) {
		return "Walk";
	}

	return "Idel";
}

void Player::UpdateAnimation() {
	GetComponent<Animator>()->CrossFade(DetermineAnimationState(), 2.0f);
}