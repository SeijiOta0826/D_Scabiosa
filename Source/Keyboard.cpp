#include "Keyboard.h"

#include <DxLib.h>
#include <cstring>

void Keyboard::Update() {
	// 1.現在の状態を前フレームへコピー
	std::memcpy(
		mOldState,
		mNowState,
		sizeof(mNowState)
	);

	// 2.現在の入力状態を取得
	GetHitKeyStateAll(mNowState);
}

bool Keyboard::IsPress(int _key) const {
	return mNowState[_key] != 0;
}

bool Keyboard::IsDown(int _key) const {
	return 
		mNowState[_key] != 0 &&
		mOldState[_key] == 0;
}

bool Keyboard::IsUp(int _key) const {
	return 
		mNowState[_key] == 0 &&
		mOldState[_key] != 0;
}