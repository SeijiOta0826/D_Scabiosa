#ifdef __INTELLISENSE__
// IntelliSenseの時だけ、VECTORのダミー定義を認識させて黙らせる
typedef struct tagVECTOR {
	float x, y, z;
} VECTOR;
#endif

#include "DxLib.h"
#include "Master.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ObjectManager.h"

SceneManager* Master::mpSceneManager = new SceneManager();	//シーンマネージャーを生成

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);	// ウインドウモードで起動
	SetGraphMode(1000, 850, 0);

	// DXライブラリ初期化
	if (DxLib_Init() == -1){
		return -1;
	}

	//Todo:	初期化処理系をここへ
	Master::mpSceneManager->Initialize();	//シーンマネージャー初期化

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏画面に設定する

	//Zバッファに書き込む準備
	SetUseZBufferFlag(true);
	SetWriteZBufferFlag(true);

	// メインループ
	while (ProcessMessage() == 0
		&& CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		SetUseLighting(TRUE);  // ライト処理ON

		SetLightDifColor(GetColorF(1.0f, 0.8f, 0.4f, 0.0f)); 	// ディフューズカラー
		SetLightAmbColor(GetColorF(3.2f, 3.2f, 3.2f, 0.0f));	// アンビエント
		int time = GetNowCount();

		//Todo:	更新処理をここへ
		Master::mpSceneManager->Update();	//シーンマネージャー更新

		ClearDrawScreen();	// 画面を初期化する

		//Todo:	描画処理をここへ
		Master::mpSceneManager->Draw();		//シーンマネージャー描画

		ScreenFlip();	// 裏画面の内容を表画面に映す

		while (GetNowCount() - time < 17) {
			//60fpsに調整
		}

		//削除する必要のあるオブジェクトがあれば削除する
		Master::mpSceneManager->GetCurrentScene()->GetObjectManager()->DeleteAll2DIfNeeded();
		Master::mpSceneManager->GetCurrentScene()->GetObjectManager()->DeleteAll3DIfNeeded();

		Master::mpSceneManager->ChangeSceneIfNeeded();	// ループする直前にシーン遷移チェックを入れておく
	}

	Master::mpSceneManager->Finalize();	//シーンマネージャー終了処理
	delete  Master::mpSceneManager;	//シーンマネージャー解放

	DxLib_End();	// DXライブラリ使用の終了
	return 0;	//ソフトの終了
}