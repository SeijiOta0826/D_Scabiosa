#pragma once

class Mouse
{
public:
	Mouse() = default;
	~Mouse() = default;

	void Update();

	bool IsPressed(int _button) const;
	bool IsDown(int _button) const;
	bool IsUp(int _button) const;

	int GetX() const;
	int GetY() const;
	int GetWheel() const;

private:
	int mNowState = 0;
	int mOldState = 0;

	int mX = 0;
	int mY = 0;

	int mWheel = 0;
};