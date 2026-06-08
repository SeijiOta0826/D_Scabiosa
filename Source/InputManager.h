#pragma once
#include "DxLib.h"
/*
キー入力に関する補助関数
DXLibに存在しないので自作
*/

//キー入力の重複防止のための、
	//キー入力モードの種類
enum class KeyInputMode
{
	MODE_NORMAL = 0,	//通常時
	MODE_NEXTSTAGESELECT,	//BlackBox選択時
};

struct Stick {
	float x;       // 横軸（-1.0 ～ 1.0）
	float y;       // 縦軸（-1.0 ～ 1.0）
	float length;  // 倒し具合（0.0 ～ 1.0）
};

struct StickInfo {
	Stick left;	//左スティック
	Stick Right;	//右スティック
};

class InputManager
{

public:
	// コンストラクタ
	InputManager();
	// デストラクタ
	~InputManager();

	// 指定されたキーが押された瞬間だけ 1 を返す関数
	static int CheckDownKey(int KeyCode);

	// 指定されたキーが離された瞬間だけ 1 を返す関数
	static int CheckUpKey(int KeyCode);

	// 指定されたキーを押し続けている間１を返す関数
	static int CheckPressKey(int KeyCode);

	//キー入力モードのアクセサ
	static void SetKeyMode(KeyInputMode _mode) { mnKeyModeNum = _mode; }
	static bool IsKeyMode(KeyInputMode state);

	static StickInfo GetStickInfo(int pad = DX_INPUT_PAD1);
	static int CheckPadButton(int _button);

private:
	static int mDownBuffer[256];	// CheckDownKey用のキーバッファ
	static int mUpBuffer[256];		// CheckUpKey用のキーバッファ
	static int mButtonBuffer[256];	

	//現在のキー入力のモード
	static KeyInputMode mnKeyModeNum;

};
