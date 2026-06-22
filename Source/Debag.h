#pragma once
#include "DxLib.h"
#include <sstream>
#include "Vector3.h"

class Debag
{
public:
	static void Begin();											//デバック描画位置の初期化
	template<typename... Args>			
	static void Log(Args&&... args);								//任意の値を表示

	static void PosLog(const char* _format, const Vector3& _pos);	//座標の値を表示

	static void Grid3D(int _gridSize, int _gridCount);				//グリッド線(3D)の表示

private:
	inline static float mLine_yPos = 0.0f;				//描画する縦座標
	inline static const float mfMargin = 10.0f;			//描画開始の縦横微妙な隙間分の値
};