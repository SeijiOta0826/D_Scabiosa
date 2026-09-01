#include "GameScene.h"

//-- マスタデータ関係 --//
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Debag.h"
#include "Utility.h"

#include "Transform.h"
#include "Animator.h"

//-- Obj関係 --//
#include "Camera.h"
#include "Player.h"
#include "GoalFlag.h"

GameScene::GameScene()
	:Scene() {
}

GameScene::~GameScene() {

}

void GameScene::Initialize() {
	Scene::Initialize();

	auto player = SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->CreateObject<Player>();
	auto goal = SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->CreateObject<GoalFlag>();

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

	// その他デバック用の描画処理
}



