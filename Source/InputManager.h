#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"

#include <array>

enum class Button {
	Confirm,
	Cancel,

	Jump,
	Attack,
	Dash,

	Max
};

enum class Axis {
	MoveX,
	MoveY,

	LookX,
	LookY,

	Max,
};

class InputManager
{
public:
	struct ButtonBinding {
		int mnKeyboardKey = -1;
		int mnMouseButton = -1;
		int mnPadButton = -1;
	};

	struct AxisBinding {
		int mnPositiveKey = -1;
		int mnNegativeKey = -1;

		PadAxis padAxis;
	};

	struct ButtonState {
		bool Press = false;
		bool Down = false;
		bool Up = false;
	};

public:
	InputManager() = default;
	~InputManager() = default;

	static InputManager& GetInstance();

	void InitializeButton();
	void InitializeAxis();

	void Update();

	bool GetButton(Button _button) const;
	bool GetButtonDown(Button _button) const;
	bool GetButtonUp(Button _button) const;
 
	float GetAxis(Axis _axis) const;

private:
	void UpdateButtons();
	void UpdateAxes();

	bool IsButtonPressed(const ButtonBinding& _binding) const;
	bool IsButtonDown(const ButtonBinding& _binding) const;
	bool IsButtonUp(const ButtonBinding& _binding) const;

	float GetAxisValue(const AxisBinding& _binding) const;

private:
	Keyboard mKeyboard;
	Mouse mMouse;
	GamePad mGamePad;

	std::array<ButtonBinding, static_cast<size_t>(Button::Max)> mButtonBindings;
	std::array<AxisBinding, static_cast<size_t>(Axis::Max)> mAxisBindings;

	std::array<ButtonState, static_cast<size_t>(Button::Max)> mButtonStates;
	std::array<float, static_cast<size_t>(Axis::Max)> mAxisStates;
};