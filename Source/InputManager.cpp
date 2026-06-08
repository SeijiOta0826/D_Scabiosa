#include "InputManager.h"
#include "DxLib.h"
#include <cmath>

// 静的メンバ変数の初期化
int InputManager::mDownBuffer[256] = { 0 };
int InputManager::mUpBuffer[256] = { 0 };

int InputManager::mButtonBuffer[256] = { 0 };
KeyInputMode InputManager::mnKeyModeNum = KeyInputMode::MODE_NORMAL;

// コンストラクタ
InputManager::InputManager()
{
	mnKeyModeNum = KeyInputMode::MODE_NORMAL;
}

// デストラクタ
InputManager::~InputManager()
{

}


// スティック入力取得関数
StickInfo InputManager::GetStickInfo(int pad)
{
	StickInfo stick{};

	// アナログスティック入力（-1000 ～ 1000）
	int x_left = 0;
	int y_left = 0;
	int x_right = 0;
	int y_right = 0;
	
	GetJoypadAnalogInput(&x_left, &y_left, pad);
	GetJoypadAnalogInputRight(&x_right, &y_right, pad);

	// -1.0 ～ 1.0 に正規化
	stick.left.x = x_left / 1000.0f;
	stick.left.y = y_left / 1000.0f;
	stick.Right.x = x_right / 1000.0f;
	stick.Right.y = y_right / 1000.0f;

	// 倒し具合（ベクトルの長さ）
	stick.left.length = sqrtf(stick.left.x * stick.left.x + stick.left.y * stick.left.y);
	if (stick.left.length > 1.0f) stick.left.length = 1.0f;
	// 倒し具合（ベクトルの長さ）
	stick.Right.length = sqrtf(stick.Right.x * stick.Right.x + stick.Right.y * stick.Right.y);
	if (stick.Right.length > 1.0f) stick.Right.length = 1.0f;

	// デッドゾーン（小さな入力を0扱い）
	const float DEAD_ZONE = 0.1f;
	if (stick.left.length < DEAD_ZONE) {
		stick.left.x = stick.left.y = 0.0f;
		stick.left.length = 0.0f;
	}

	if (stick.Right.length < DEAD_ZONE) {
		stick.Right.x = stick.Right.y = 0.0f;
		stick.Right.length = 0.0f;
	}

	return stick;
}

int InputManager::CheckPadButton(int _button) {

	// 戻り値用の変数を用意
	int result = 0;
	int nButtonState = GetJoypadInputState(DX_INPUT_PAD1) & _button;

	if (mButtonBuffer[_button] == 0 && nButtonState > 0) {
		result = 1;
	}

	mButtonBuffer[_button] = nButtonState;

	if (mButtonBuffer[_button] > 1 && nButtonState == 0) {
		mButtonBuffer[_button] = 0;
	}
	return result;
}

int InputManager::CheckDownKey(int KeyCode)
{
	// 戻り値用の変数を用意
	int result = 0;

	// 指定キーの現在の状態を取得
	int keyState = CheckHitKey(KeyCode);

	// 前回キーが押されておらず、かつ、現在キーが押されていたら「キーを押した瞬間」とする
	if(mDownBuffer[KeyCode] == 0 && keyState == 1)
	{
		result = 1;
	}

	// 現在のキー状態をバッファに格納
	mDownBuffer[KeyCode] = keyState;

	return result;
}

// 指定されたキーが離された瞬間だけ 1 を返す関数
int InputManager::CheckUpKey(int KeyCode)
{
	// 戻り値用の変数を用意
	int result = 0;

	// 指定キーの現在の状態を取得
	int keyState = CheckHitKey(KeyCode);

	// 前回キーが押されており、かつ、現在キーが押されていなかったら「キーを離した瞬間」とする
	if(mUpBuffer[KeyCode] == 1 && keyState == 0)
	{
		result = 1;
	}

	// 現在のキー状態をバッファに格納
	mUpBuffer[KeyCode] = keyState;

	return result;
}

// 指定されたキーを押し続けている間１を返す関数
int InputManager::CheckPressKey(int KeyCode)
{
	return CheckHitKey(KeyCode);
}

//現Keyモードが指定のKeyモードであるかを示す
bool InputManager::IsKeyMode(KeyInputMode state)
{
	return mnKeyModeNum == state;
}