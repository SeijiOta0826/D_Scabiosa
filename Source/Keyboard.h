#pragma once

class Keyboard
{
public:
	Keyboard() = default;
	~Keyboard() = default;

	void Update();

	bool IsPress(int _key) const;
	bool IsDown(int _key) const;
	bool IsUp(int _key) const;

private:
	char mNowState[256]{};	//現フレームに押しているキー
	char mOldState[256]{};	//前フレームに押しているキー
};