#pragma once

// クラスの前方宣言
class Scene;

class SceneManager
{
public: 
	//シーン種類
	enum SCENE_TYPE {
		SCENE_NONE = 0,

		SCENE_GAME = 1,	//ゲームシーン
	};

public:
	SceneManager();
	~SceneManager();

	void Initialize();
	void Update(float _deltaTime);
	void Draw();
	void Finalize();

	void ChangeSceneIfNeeded();		// シーン遷移（切り替え処理）が必要な状態なら遷移処理する

	void SetNextScene(SCENE_TYPE next) { mnNextSceneType = next;}	// 次に遷移するシーンの設定

	Scene* GetCurrentScene() { return mpCurrentScene; }	// 現在シーンの取得
	SCENE_TYPE GetCurrentSceneType() { return mnSceneType; }	//シーンタイプの取得関数

private:
	SCENE_TYPE mnSceneType;      // 現在シーンのタイプ
	SCENE_TYPE mnNextSceneType;  // 次シーンのタイプ
	Scene* mpCurrentScene;       // 現在シーンのポインタ
};