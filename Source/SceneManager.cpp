#include "SceneManager.h"
#include "Scene.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"

SceneManager::SceneManager()
	:mnSceneType(SCENE_TYPE::SCENE_NONE)
	, mnNextSceneType(SCENE_TYPE::SCENE_NONE)
	, mpCurrentScene(nullptr) {

}


SceneManager::~SceneManager() {

}

SceneManager& SceneManager::GetInstance() {
	static SceneManager instance;
	return instance;
}

void SceneManager::Initialize() {
	mnNextSceneType = SCENE_TYPE::SCENE_GAME;	//初期シーンの設定
	ChangeSceneIfNeeded();	//シーン遷移処理
}

void SceneManager::Update(float _deltaTime) {
	mpCurrentScene->Update(_deltaTime);	//シーン更新
}

void SceneManager::Draw() {
	mpCurrentScene->Draw();		//シーン描画
}

void SceneManager::Finalize() {
	mpCurrentScene->Finalize();
}

void SceneManager::ChangeSceneIfNeeded() {
	if (mnSceneType == mnNextSceneType)	return;	//シーン設定に変更がなければ以降スルー

	//以降、シーン変更があった場合

	if (mpCurrentScene != nullptr)	mpCurrentScene->Finalize();		//前シーン終了処理

	mnSceneType = mnNextSceneType;	//次シーンにするためシーンタイプを更新

	//mnSCeneType に応じてシーンを生成する
	switch (mnSceneType)
	{
		case SCENE_TYPE::SCENE_TITLE:
		mpCurrentScene = new TitleScene();
		break;
	case SCENE_TYPE::SCENE_GAME:
		mpCurrentScene = new GameScene();
		break;
		case SCENE_TYPE::SCENE_RESULT:
		mpCurrentScene = new ResultScene();
		break;
	default:
		break;
	}

	mpCurrentScene->Initialize();	//シーンの生成がされているはずなので、初期化処理を呼んでおく
}