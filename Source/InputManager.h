#pragma once
#include "DxLib.h"
/*
キー入力に関する補助関数
DXLibに存在しないので自作
*/

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
	InputManager();
	~InputManager();

	static InputManager& GetInstance();	//インスタンスの取得

	//-- キーボード入力 --//
	static int CheckDownKey(int KeyCode);	// 指定されたキーが押された瞬間だけ 1 を返す関数
	static int CheckUpKey(int KeyCode);		// 指定されたキーが離された瞬間だけ 1 を返す関数
	static int CheckPressKey(int KeyCode);	// 指定されたキーを押し続けている間１を返す関数

	//-- コントローラー入力 --//
	static StickInfo GetStickInfo(int pad = DX_INPUT_PAD1);	//スティックの入力取得
	static int CheckPadButton(int _button);					//指定されたボタンが押された瞬間だけ 1 を返す関数

private:
	static int mDownBuffer[256];	// CheckDownKey用のキーバッファ
	static int mUpBuffer[256];		// CheckUpKey用のキーバッファ
	static int mButtonBuffer[256];
};
