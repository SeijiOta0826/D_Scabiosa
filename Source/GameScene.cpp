#include "GameScene.h"

//-- マスタデータ関係 --//
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Debag.h"
#include "Utility.h"

//-- Obj関係 --//
#include "Camera.h"
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
	DebagDraw();
	Scene::Draw();
}

void GameScene::Finalize() {

}

void GameScene::DebagDraw() {

	Debag::Grid3D(500,5000);	//グリッド線の表示

	Debag::Begin();	//デバック表示位置の初期化
	
	auto pPlayer = 
		SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->GetObject3DByTag(Object3D::OBJ_PLAYER);

	Debag::PosLog("PlayerPos: ", pPlayer->GetPosition());	//Playerの座標表示

	Vector3 vCameraPos =
		Camera::GetInstance().GetPosition();

	Debag::PosLog("CameraPos: ", vCameraPos);				//カメラの座標表示
}



