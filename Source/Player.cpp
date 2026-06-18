#include "Player.h"

#include "Model.h"

#include "InputManager.h"
#include "Physics.h"

Player::Player() 
	:Object3D(mvPosition)
	, mpModel(std::make_unique<Model>("Resource/3D/Paladin/Mesh.mv1", mvPosition, true))
	, mpPhysics(std::make_unique<Physics>()){
	this->SetTag(OBJ_PLAYER);	//タグを付与
}

Player::~Player() {

}

void Player::Update(float _deltaTime) {

	if (InputManager::GetInstance().CheckDownKey(KEY_INPUT_D)) {
		mpPhysics->AddForce(VGet(10.0f, 0.0f, 0.0f));
	}

	this->SetPosition(VAdd(mvPosition, mpPhysics->Update(_deltaTime)));
	mpModel->SetPosition(mvPosition);
	Object3D::Update(_deltaTime);
	mpModel->Update(_deltaTime);
}

void Player::Draw() {
	Object3D::Draw();
	mpModel->Draw();
}