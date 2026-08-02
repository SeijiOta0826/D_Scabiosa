#include "GamePad.h"

#include <DxLib.h>

namespace {
	constexpr int PAD_ID = DX_INPUT_PAD1;
	constexpr float PAD_ANALOG_MAX = 1000.0f;
}

void GamePad::Update() {
	mOldState = mNowState;

	mNowState = GetJoypadInputState(PAD_ID);

	mbConnected = mNowState != -1;

	if (!mbConnected) {
		mNowState = 0;

		mLeftStick = Vector2();
		mRightStick = Vector2();

		mfLeftTrigger = 0;
		mfRightTrigger = 0;

		return;
	}

	// 1.スティックの入力情報を取得
	int lx, ly;
	GetJoypadAnalogInput(
		&lx,
		&ly,
		PAD_ID
	);

	// 2.スティックの倒し具合の割合を取得
	mLeftStick.x = static_cast<float>(lx) / PAD_ANALOG_MAX;
	mLeftStick.y = -static_cast<float>(ly) / PAD_ANALOG_MAX;

	int rx, ry;
	GetJoypadAnalogInputRight(
		&rx,
		&ry,
		PAD_ID
	);

	mRightStick.x = static_cast<float>(rx) / PAD_ANALOG_MAX;
	mRightStick.y = -static_cast<float>(ry) / PAD_ANALOG_MAX;
}

bool GamePad::IsConnected() const {
	return mbConnected;
}

bool GamePad::IsPressed(int _button) const{
	return (mNowState & _button) != 0;
}

bool GamePad::IsDown(int _button) const {
	return
		(mNowState & _button) != 0 &&
		(mOldState & _button) == 0;
}

bool GamePad::IsUp(int _button) const {
	return 
		(mNowState & _button) == 0 &&
		(mOldState & _button) != 0;
}

Vector2 GamePad::GetLeftStick() const {
	return mLeftStick;
}

Vector2 GamePad::GetRightStick() const {
	return mRightStick;
}