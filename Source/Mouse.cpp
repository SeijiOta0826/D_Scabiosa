#include "Mouse.h"

#include <DxLib.h>
void Mouse::Update() {
	mOldState = mNowState;

	mNowState = GetMouseInput();

	GetMousePoint(&mX, &mY);

	mWheel = GetMouseWheelRotVol();
}

bool Mouse::IsPressed(int _button) const {
	return (mNowState & _button) != 0;
}

bool Mouse::IsDown(int _button) const {
	return
		(mNowState & _button) != 0 &&
		(mOldState & _button) == 0;
}

bool Mouse::IsUp(int _button) const {
	return
		(mNowState & _button) == 0 &&
		(mOldState & _button) != 0;
}

int Mouse::GetX() const{
	return mX;
}

int Mouse::GetY() const {
	return mY;
}

int Mouse::GetWheel() const {
	return mWheel;
}