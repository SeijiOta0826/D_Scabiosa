#include "InputManager_test.h"
#include <cstring>
#include <cmath>
#include <algorithm>

InputManager_test& InputManager_test::GetInstance() {
	static InputManager_test instance;
	return instance;
}

void InputManager_test::Initialize() {
	mBindings[(int)Button::Confirm] =
	{
		KEY_INPUT_RETURN,
		PAD_INPUT_1
	};

	mBindings[(int)Button::Cancel] =
	{
		KEY_INPUT_ESCAPE,
		PAD_INPUT_2
	};

	mBindings[(int)Button::Jump] =
	{
		KEY_INPUT_SPACE,
		PAD_INPUT_3
	};

	mBindings[(int)Button::Attack] =
	{
		KEY_INPUT_Z,
		PAD_INPUT_4
	};

	mBindings[(int)Button::Dash] =
	{
		KEY_INPUT_LSHIFT,
		PAD_INPUT_5
	};
}

void InputManager_test::Update() {
	UpdateKeyboard();
	UpdateGamePad();
	UpdateButtons();
}

void InputManager_test::UpdateKeyboard() {
	// 1.現在のキー入力状態をワンフレーム前のキー入力状態へコピー
	memcpy(
		mOldKey,
		mNowKey,
		sizeof(mNowKey)
	);

	// 2.現在のキー入力状態を取得
	GetHitKeyStateAll(mNowKey);
}

void InputManager_test::UpdateGamePad() {
	mnPadState =
		GetJoypadInputState(DX_INPUT_PAD1);

	// 1.スティックの入力情報を取得
	int lx, ly;
	GetJoypadAnalogInput(
		&lx,
		&ly,
		DX_INPUT_PAD1
	);

	constexpr float MAX_STICK = 1000.0f;

	// 2.スティックの倒し具合の割合を取得
	mLeftStick.x = lx / MAX_STICK;
	mLeftStick.y = ly / MAX_STICK;

	mLeftStick.length =
		(std::min)(
			1.0f,
			sqrtf(
				mLeftStick.x * mLeftStick.x +
				mLeftStick.y * mLeftStick.y
			)
		);

	int rx, ry;
	GetJoypadAnalogInputRight(
		&rx,
		&ry,
		DX_INPUT_PAD1
	);

	mRightStick.x = rx / MAX_STICK;
	mRightStick.y = ry / MAX_STICK;

	mRightStick.length =
		(std::min)(
			1.0f,
			sqrtf(mRightStick.x * mRightStick.x +
				mRightStick.y * mRightStick.y
			)
		);
}

void InputManager_test::UpdateButtons() {
	for (int i = 0;
		i < (int)Button::Max;
		i++) {
		const auto& binding = mBindings[i];

		bool nowKeyboard =
			binding.mnKeyboardKey != -1 &&
			mNowKey[binding.mnKeyboardKey];

		bool oldKeyboard =
			binding.mnKeyboardKey != -1 &&
			mOldKey[binding.mnKeyboardKey];

		bool nowPad =
			binding.mnPadButton != -1 &&
			(mnPadState & binding.mnPadButton);

		bool now =
			nowKeyboard || nowPad;

		bool old =
			oldKeyboard;

		auto& state =
			mButtonStates[i];

		state.Press = now;

		state.Down =
			now && !old;

		state.Up =
			!now && old;
	}
}

bool InputManager_test::GetButton(
	Button _button
) const {
	return mButtonStates[(int)_button].Press;
}

bool InputManager_test::GetButtonDown(
	Button _button
) const {
	return mButtonStates[(int)_button].Down;
}

bool InputManager_test::GetButtonUp(
	Button _button
) const {
	return mButtonStates[(int)_button].Up;
}

const InputManager_test::Stick& 
InputManager_test::GetLeftStick() const {
	return mLeftStick;
}

const InputManager_test::Stick&
InputManager_test::GetRightStick() const {
	return mRightStick;
}

