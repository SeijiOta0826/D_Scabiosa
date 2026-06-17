#include "Player.h"

#include "Model.h"

#include "InputManager.h"
#include "Physics.h"

Player::Player() 
	:Object3D(mvPosition){
	mpModel = 
		new Model("Resource/3D/Paladin/Mesh.mv1", mvPosition,true);	//モデルデータの生成

	mpPhysics = std::make_unique<Physics>();
	this->SetTag(OBJ_PLAYER);	//タグを付与
}

Player::~Player() {
	if(mpModel != nullptr)	delete mpModel;	//モデルデータを解放
}

void Player::Update(float _deltaTime) {

	if (InputManager::CheckDownKey(KEY_INPUT_D)) {
		mpPhysics->AddForce(VGet(10.0f, 0.0f, 0.0f));
	}

	Object3D::Update(_deltaTime);
	mpModel->Update(_deltaTime);

	mpModel->SetPosition(VAdd(mvPosition,mpPhysics->Update(_deltaTime)));
}

void Player::Draw() {
	Object3D::Draw();
	mpModel->Draw();
}