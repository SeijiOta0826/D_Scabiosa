#include "DxLib.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "InputManager.h"

#include "Utility.h"

#include "SceneManager.h"
#include "Camera.h"
#include "ResourceManager.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);	// ウインドウモードで起動
	SetGraphMode(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, 0);

	// DXライブラリ初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	//Todo:	初期化処理系をここへ
	SceneManager::GetInstance().Initialize();	//シーンマネージャー初期化
	Camera::GetInstance().Initialize();
	InputManager::GetInstance().InitializeButton();
	InputManager::GetInstance().InitializeAxis();

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏画面に設定する

	//Zバッファに書き込む準備
	SetUseZBufferFlag(true);
	SetWriteZBufferFlag(true);

	SetLightDifColor(GetColorF(1.0f, 0.8f, 0.4f, 0.0f)); 	// ディフューズカラー
	SetLightAmbColor(GetColorF(3.2f, 3.2f, 3.2f, 0.0f));	// アンビエント

	int prevTime = GetNowCount();
	// メインループ
	while (ProcessMessage() == 0
		&& CheckHitKey(KEY_INPUT_ESCAPE) == 0
		) {
		SetUseLighting(TRUE);  // ライト処理ON

		int time = GetNowCount();

		int currentTime = GetNowCount();	//現在の時間を取得
		float deltaTime = (currentTime - prevTime) / 1000.0f;	//msをsに変換(deltaTimeを取得)
		prevTime = currentTime;	//prevTimeを更新

		//Todo:	更新処理をここへ
		SceneManager::GetInstance().Update(deltaTime);		//シーンマネージャー更新
		Camera::GetInstance().Update(deltaTime);
		InputManager::GetInstance().Update();

		ClearDrawScreen();	// 画面を初期化する

		//Todo:	描画処理をここへ
		SceneManager::GetInstance().Draw();		//シーンマネージャー描画

		ScreenFlip();	// 裏画面の内容を表画面に映す

		while (GetNowCount() - currentTime < 17) {
			//60fpsに調整
		}

		SceneManager::GetInstance().ChangeSceneIfNeeded();	// ループする直前にシーン遷移チェックを入れておく
	}

	SceneManager::GetInstance().Finalize();	//シーンマネージャー終了処理
	Camera::GetInstance().Finalize();	//カメラ終了処理

	DxLib_End();	// DXライブラリ使用の終了
	return 0;	//ソフトの終了
}