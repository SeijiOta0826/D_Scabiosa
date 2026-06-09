#pragma once
#include "DxLib.h"
#include <sstream>

class Debag
{
public:
	static void Begin();
	template<typename... Args> 
	static void Log(const char* _format, Args&&... args);

private:
	inline static float mLine_yPos = 0.0f;	//描画する縦座標
	const float mfMargin = 10.0f;	//描画開始の縦横微妙な隙間分の値
};