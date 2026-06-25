#include "Debag.h"

void Debag::Begin() {
	mLine_yPos = 10.0f;	//描画開始y座標に初期化
}

void Debag::PosLog(const char* _format, const Vector3& _pos) {
	Log(_format, "( ", _pos.x, ",", _pos.y, ",", _pos.z, " )");
}

void Debag::Grid3D(int _gridSize, int _gridCount) {
	int half = _gridSize * _gridCount / 2;	//原点が中心になるように半分の規模を算出

	//X方向の線
	for (int z = -half; z <= half; z += _gridSize) {
		DrawLine3D(
			VGet(-half, 0.0f, (float)z),
			VGet(half, 0.0f, (float)z),
			GetColor(0, 0, 0)
		);
	}

	//Z方向の線
	for (int x = -half; x <= half; x += _gridSize) {
		DrawLine3D(
			VGet((float)x, 0.0f, -half),
			VGet((float)x, 0.0f, half),
			GetColor(0, 0, 0)
		);
	}
}