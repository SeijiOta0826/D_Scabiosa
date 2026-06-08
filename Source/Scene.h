#pragma once

class ObjectManager;

class Scene
{
public:

	Scene();
	~Scene();

	virtual void Initialize() = 0;	//初期化処理

	virtual void Update(float _deltaTime);	//更新処理
	virtual void Draw();	//描画処理

	virtual void Finalize() = 0;	//終了処理

	ObjectManager* GetObjectManager() { return mpObjectManager; }	//オブジェクトマネージャーの取得
private:
	ObjectManager* mpObjectManager;	//各シーンで管理するObjectManager
};
