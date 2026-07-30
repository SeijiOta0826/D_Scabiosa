#pragma once
#include "DxLib.h"

class InputManager_test
{
public:
	enum class Button {
		Confirm,
		Cancel,

		MoveForward,
		MoveBackward,
		MoveLeft,
		MoveRight,

		Jump,
		Attack,
		Dash,

		Max
	};

	struct ButtonState {
		bool Press = false;
		bool Down = false;
		bool Up = false;
	};

	struct ButtonBinding {
		int mnKeyboardKey = -1;
		int mnPadButton = -1;
	};

	struct Stick {
		float x = 0.0f;
		float y = 0.0f;

		float length = 0.0f;
	};

public:
	static InputManager_test& GetInstance();

	void Initialize();

	void Update();

	bool GetButton(Button _button) const;
	bool GetButtonDown(Button _button) const;
	bool GetButtonUp(Button _button) const;
 
	const Stick& GetLeftStick() const;
	const Stick& GetRightStick() const;

private:
	void UpdateKeyboard();
	void UpdateGamePad();
	void UpdateButtons();

private:
	char mNowKey[256]{};
	char mOldKey[256]{};

	int mnPadState = 0;

	Stick mLeftStick;
	Stick mRightStick;

	ButtonBinding mBindings[(int)Button::Max];

	ButtonState mButtonStates[(int)Button::Max];
};