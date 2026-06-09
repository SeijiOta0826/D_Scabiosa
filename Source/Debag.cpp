#include "Debag.h"

void Debag::Begin() {
	mLine_yPos = 10.0f;	//描画開始y座標に初期化
}

template<typename... Args>
void Debag::Log(const char* _format, Args&&... args) {
	std::stringstream ss;

	(ss << ... << args);

	DrawString(
		mfMargin,
		mfMargin + mLine_yPos * (mfMargin * 2),
		ss.str().c_str(),
		GetColor(255, 255, 255));

	++mLine_yPos;
}