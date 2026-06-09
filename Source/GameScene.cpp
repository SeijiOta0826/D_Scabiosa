#include "GameScene.h"

//-- マスタデータ関係 --//
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Utility.h"

//-- Obj関係 --//
#include "Player.h"

GameScene::GameScene()
	:Scene() {
}

GameScene::~GameScene() {

}

void GameScene::Initialize() {
	Player* pPlayer = new Player();
}

void GameScene::Update(float _deltaTime) {
	Scene::Update(_deltaTime);
}

void GameScene::Draw() {
	Scene::Draw();
}

void GameScene::Finalize() {

}

void GameScene::DebagDraw() {


	auto pPlayer = 
		Master::mpSceneManager->GetCurrentScene()->GetObjectManager()->GetObject3DByTag(Object3D::OBJ_PLAYER);
	//DrawFormatString(0.0f,)
}



