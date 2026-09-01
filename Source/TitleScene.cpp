#include "TitleScene.h"
#include "InputManager.h"

#include "SceneManager.h"

#include <DxLib.h>
#include "Utility.h"
void TitleScene::Initialize() {
	Scene::Initialize();

	mFontHandle = CreateFontToHandle(
		nullptr,    // フォント名
		64,         // サイズ
		3           // 太さ
	);
}

void TitleScene::Finalize() {
	Scene::Finalize();
}

void TitleScene::Update(float _deltaTime) {
	Scene::Update(_deltaTime);

	if (InputManager::GetInstance().GetButtonDown(Button::Confirm)) {
		SceneManager::GetInstance().SetNextScene(SCENE_TYPE::SCENE_GAME);
	}
}

void TitleScene::Draw() {
	Scene::Draw();

	DrawStringToHandle(
		Utility::SCREEN_WIDTH / 2 - 150.0f,
		Utility::SCREEN_HEIGHT / 2 - 50.0f,
		"TitleScene",
		GetColor(0, 0, 0),
		mFontHandle
	);

	DrawStringToHandle(
		Utility::SCREEN_WIDTH / 2 - 150.0f,
		Utility::SCREEN_HEIGHT / 2 + 50.0f,
		"- Eneter - ",
		GetColor(0, 0, 0),
		mFontHandle
	);
}
