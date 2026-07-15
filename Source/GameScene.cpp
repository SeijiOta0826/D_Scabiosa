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
#include "Player_test.h"

GameScene::GameScene()
	:Scene() {
}

GameScene::~GameScene() {

}

void GameScene::Initialize() {
	/*Player* pPlayer = new Player();
	pPlayer->AddAnimation(ANIMATION_NEUTRAL, "Resource/3D/Paladin/Idle.mv1");
	pPlayer->AddAnimation(ANIMATION_WALKING, "Resource/3D/Paladin/Walking.mv1");
	pPlayer->AddAnimation(ANIMATION_RUN, "Resource/3D/Paladin/Running.mv1");*/

	auto player = SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->CreateObject<Player_test>();
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
	
	auto pPlayer = SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->FindObject<Player_test>();

	Debag::PosLog("PlayerPos: ", pPlayer->GetComponent<Transform>()->GetPosition());	//Playerの座標表示
	Debag::Log("アニメーション番号: ", pPlayer->GetComponent<Animator>()->GetCurrentAnimationName());
	Vector3 vCameraPos =
		Camera::GetInstance().GetPosition();

	Debag::PosLog("CameraPos: ", vCameraPos);				//カメラの座標表示
}



