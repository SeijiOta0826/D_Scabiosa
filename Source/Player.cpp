#include "Player.h"

#include "Model.h"

#include "InputManager.h"
#include "Physics.h"

#include "Camera.h"


Player::Player() 
	:Object3D(mvPosition)
	, mpModel(std::make_unique<Model>("Resource/3D/Paladin/Mesh.mv1", mvPosition))
	, mpPhysics(std::make_unique<Physics>()){
	this->SetTag(OBJ_PLAYER);	//タグを付与
}

Player::~Player() {

}

// アニメーション追加
void Player::AddAnimation(AnimationState state, std::string filename){
	mpModel->AddAnimation(state, filename);
}

void Player::Update(float _deltaTime) {
	//mpModel->ChangeAnimation(ANIMATION_NEUTRAL);
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

	if (InputManager::GetInstance().CheckPressKey(KEY_INPUT_W)) vMoveVec = vMoveVec + vUpMoveVector;
	if (InputManager::GetInstance().CheckPressKey(KEY_INPUT_A)) vMoveVec = vMoveVec + vLeftMoveVector;
	if (InputManager::GetInstance().CheckPressKey(KEY_INPUT_S)) vMoveVec = vMoveVec + (vUpMoveVector * -1.0f);
	if (InputManager::GetInstance().CheckPressKey(KEY_INPUT_D)) vMoveVec = vMoveVec + (vLeftMoveVector * -1.0f);

	mpPhysics->AddForce(vMoveVec * fMovePower);
}