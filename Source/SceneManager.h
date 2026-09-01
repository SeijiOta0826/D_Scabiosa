#pragma once

// クラスの前方宣言
class Scene;

//シーン種類
enum class SCENE_TYPE {
	SCENE_NONE = 0,

	SCENE_TITLE = 1,	// タイトルシーン
	SCENE_GAME = 2,		// ゲームシーン
	SCENE_RESULT = 3,	// リザルトシーン
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	static SceneManager& GetInstance();	//インスタンスを取得

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