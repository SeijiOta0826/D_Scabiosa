#include "Player.h"

#include "Model.h"

#include "InputManager.h"
#include "Physics.h"

#include "Camera.h"


Player::Player() 
	:Object3D(mvPosition)
	, mpModel(std::make_unique<Model>("Resource/3D/Paladin/Mesh.mv1", mvPosition, true))
	, mpPhysics(std::make_unique<Physics>()){
	this->SetTag(OBJ_PLAYER);	//タグを付与
}

Player::~Player() {

}

void Player::Update(float _deltaTime) {
	Move();	//移動処理

	this->SetPosition(mvPosition + mpPhysics->Update(_deltaTime));
	mpModel->SetPosition(mvPosition);
	Object3D::Update(_deltaTime);
	mpModel->Update(_deltaTime);
}

void Player::Draw() {
	Object3D::Draw();
	mpModel->Draw();
}

void Player::Move() {
	Vector3 vMoveVec;	//移動方向

	//Todo : パワーが徐々に上がったり下がったりするようにする
	float fMovePower = 1.0f;	//(仮)移動速度

	Vector3 vUpMoveVector;		//カメラの前方向ベクトル(奥)
	Vector3 vLeftMoveVector;	//カメラの左方向ベクトル

	{
		//カメラから見た奥方向を取得
		vUpMoveVector =
			Camera::GetInstance().GetLookAtPosition() - Camera::GetInstance().GetPosition();
		vUpMoveVector.y = 0;	

		//カメラから見た左方向を取得
		vLeftMoveVector = 
			vUpMoveVector
	}
	if (InputManager::GetInstance().CheckDownKey(KEY_INPUT_W)) mpPhysics->AddForce(VGet(10.0f, 0.0f, 0.0f));
	if (InputManager::GetInstance().CheckDownKey(KEY_INPUT_A)) mpPhysics->AddForce(VGet(10.0f, 0.0f, 0.0f));
	if (InputManager::GetInstance().CheckDownKey(KEY_INPUT_S)) mpPhysics->AddForce(VGet(10.0f, 0.0f, 0.0f));
	if (InputManager::GetInstance().CheckDownKey(KEY_INPUT_D)) mpPhysics->AddForce(VGet(10.0f, 0.0f, 0.0f));
	
}