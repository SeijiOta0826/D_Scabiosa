#include "GameScene.h"

//-- マスタデータ関係 --//
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Debag.h"
#include "Utility.h"
#include "ModelUtility.h"

#include "Transform.h"
#include "Animator.h"

//-- Obj関係 --//
#include "Camera.h"
#include "Player.h"
#include "TestBox.h"

GameScene::GameScene()
	:Scene() {
}

GameScene::~GameScene() {

}

void GameScene::Initialize() {
	Scene::Initialize();

	auto player = SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->CreateObject<Player>();

	auto box = SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->CreateObject<TestBox>();
	box->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1500.0f));

	Camera::GetInstance().SetTarget(player);
}

void GameScene::Finalize() {
	Scene::Finalize();
}

void GameScene::Update(float _deltaTime) {
	Scene::Update(_deltaTime);
}

void GameScene::Draw() {
	DebagDraw();
	Scene::Draw();
}

void GameScene::DebagDraw() {

	Debag::Grid3D(500,5000);	//グリッド線の表示

	Debag::Begin();	//デバック表示位置の初期化
	
	auto pPlayer = SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->FindObject<Player>();
	Debag::PosLog("PlayerPos: ", pPlayer->GetComponent<Transform>()->GetPosition());	//Playerの座標表示

	auto i = pPlayer->GetComponent<Animator>()->GetCurrentAnimationName();
	Debag::Log("アニメーション番号: ", pPlayer->GetComponent<Animator>()->GetCurrentAnimationName());
	Vector3 vCameraPos;
		//Camera::GetInstance().GetPosition();

	Debag::PosLog("CameraPos: ", vCameraPos);				//カメラの座標表示
}



