#include "ResultScene.h"
#include "InputManager.h"

#include "SceneManager.h"

#include <DxLib.h>
#include "Utility.h"
void ResultScene::Initialize() {
	Scene::Initialize();

	mFontHandle = CreateFontToHandle(
		nullptr,    // フォント名
		64,         // サイズ
		3           // 太さ
	);
}

void ResultScene::Finalize() {
	Scene::Finalize();
}

void ResultScene::Update(float _deltaTime) {
	Scene::Update(_deltaTime);

	if (InputManager::GetInstance().GetButtonDown(Button::Confirm)) {
		SceneManager::GetInstance().SetNextScene(SCENE_TYPE::SCENE_TITLE);
	}
}

void ResultScene::Draw() {
	Scene::Draw();

	DrawStringToHandle(
		Utility::SCREEN_WIDTH / 2 - 150.0f,
		Utility::SCREEN_HEIGHT / 2 - 50.0f,
		"ResultScene",
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