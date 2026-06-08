#pragma once

//#include "ResourceManager.h"
//#include "Loading.h"

#include "SceneManager.h"
//#include "Camera.h"

class Master 
{
public:
	
	//static ResourceManager* mpResource;	//リソース,ロード関係
	//static LoadingManager* mpLoading;	//ローディングで用いる

	static SceneManager* mpSceneManager;	//シーン
	//static Camera* mpCamera;	//カメラ
};
