#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
	:mnSceneType(SCENE_TYPE::SCENE_NONE)
	, mnNextSceneType(SCENE_TYPE::SCENE_NONE)
	, mpCurrentScene(nullptr) {

}


SceneManager::~SceneManager() {

}

void SceneManager::Initialize() {
	mnNextSceneType = SCENE_TYPE::SCENE_NONE;	//初期シーンの設定
	ChangeSceneIfNeeded();	//シーン遷移処理
}

void SceneManager::Update(float _deltaTime) {
	mpCurrentScene->Update(_deltaTime);	//シーン更新
}

void SceneManager::Draw(){
	mpCurrentScene->Draw();		//シーン描画
}

void SceneManager::Finalize(){

}

void SceneManager::ChangeSceneIfNeeded(){
	if (mnSceneType == mnNextSceneType)	return;	//シーン設定に変更がなければ以降スルー

	//以降、シーン変更があった場合

	if (mpCurrentScene != nullptr)	mpCurrentScene->Finalize();		//前シーン終了処理
	
	mnSceneType = mnNextSceneType;	//次シーンにするためシーンタイプを更新

	//mnSCeneType に応じてシーンを生成する
	/*switch (mnSceneType)
	{

	default:
		break;

	}*/

	mpCurrentScene->Initialize();	//シーンの生成がされているはずなので、初期化処理を呼んでおく
}