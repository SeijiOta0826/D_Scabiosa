#pragma once
#include "DxLib.h"
#include <sstream>
#include "Vector3.h"

class Debag
{
public:
	static void Begin();											//デバック描画位置の初期化
	
	//任意の値を表示
	template<typename... Args>			
	static void Log(Args&&... args) {
		std::stringstream ss;

		(ss << ... << args);

		DrawString(
			mfMargin,
			mfMargin + mLine_yPos * (mfMargin * 2),
			ss.str().c_str(),
			GetColor(255, 255, 255));

		++mLine_yPos;
	}

	static void PosLog(const char* _format, const Vector3& _pos);	//座標の値を表示

	static void DrawSphere(
		const Vector3& _position,
		float _radius,
		int _color
	);

	static void DrawDebugBox(const Vector3& center, const Vector3& size, unsigned int color);

	static void Grid3D(int _gridSize, int _gridCount);				//グリッド線(3D)の表示

private:
	inline static float mLine_yPos = 0.0f;				//描画する縦座標
	inline static const float mfMargin = 10.0f;			//描画開始の縦横微妙な隙間分の値
};