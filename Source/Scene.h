#pragma once
#include <memory>

class ObjectManager;

class Scene
{
public:

	Scene();
	~Scene() = default;

	virtual void Initialize() = 0;			//初期化処理

	virtual void Update(float _deltaTime);	//更新処理
	virtual void Draw();					//描画処理

	virtual void Finalize() = 0;			//終了処理

	// ObjectManagerの取得関数
	// 各SceneデータからObject情報を引っ張る際に用いる
	ObjectManager* GetObjectManager() const {
		return mpObjectManager.get();
	}

protected:
	std::unique_ptr<ObjectManager> mpObjectManager;	//ObjectManagerデータ
};
