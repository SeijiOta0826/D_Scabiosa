#include "Object3D.h"

#include "SceneManager.h"
#include "ObjectManager.h"
#include "Scene.h"

Object3D::Object3D(VECTOR initPos)
	:mvPosition(initPos)
	, mvRotation(VGet(0.0f, 0.0f, 0.0f))
	, mbDeleteFlag(false)
	, mnTag(Tag3D::None3D) {
	//SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->AddObject(this);	//Œ»ÝƒV[ƒ“‚ÌObjectManager‚ÉŽ©g(this)‚ð’Ç‰Á‚·‚é
	SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->AddObject(this);
}

Object3D::~Object3D(){

}

void Object3D::Update(float _deltaTime){

}

void Object3D::Draw(){

}