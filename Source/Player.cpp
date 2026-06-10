#include "Player.h"

#include "Model.h"

Player::Player() 
	:Object3D(mvPosition){
	mpModel = 
		new Model("Resource/3D/Paladin/Mesh.mv1", mvPosition,true);	//モデルデータの生成

	this->SetTag(OBJ_PLAYER);	//タグを付与
}

Player::~Player() {
	if(mpModel != nullptr)	delete mpModel;	//モデルデータを解放
}

void Player::Update(float _deltaTime) {
	Object3D::Update(_deltaTime);
	mpModel->Update(_deltaTime);
}

void Player::Draw() {
	Object3D::Draw();
	mpModel->Draw();
}