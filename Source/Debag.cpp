#include "Debag.h"

void Debag::Begin() {
	mLine_yPos = 10.0f;	//描画開始y座標に初期化
}

void Debag::PosLog(const char* _format, const Vector3& _pos) {
	Log(_format, "( ", _pos.x, ",", _pos.y, ",", _pos.z, " )");
}

void Debag::DrawSphere(const Vector3& _position,
	float _radius,
	int _color
) {
	DrawSphere3D(
		_position.ToDxVector(),
		_radius,
		16,
		_color,
		_color,
		FALSE
	);
}

void Debag::DrawDebugBox(const Vector3& center, const Vector3& halfSize, unsigned int color) {
	VECTOR h = halfSize.ToDxVector(); // 半分のサイズ

	// AABB（回転なし）の8頂点
	VECTOR v[8] = {
		VGet(center.x - h.x, center.y - h.y, center.z - h.z),
		VGet(center.x + h.x, center.y - h.y, center.z - h.z),
		VGet(center.x + h.x, center.y + h.y, center.z - h.z),
		VGet(center.x - h.x, center.y + h.y, center.z - h.z),
		VGet(center.x - h.x, center.y - h.y, center.z + h.z),
		VGet(center.x + h.x, center.y - h.y, center.z + h.z),
		VGet(center.x + h.x, center.y + h.y, center.z + h.z),
		VGet(center.x - h.x, center.y + h.y, center.z + h.z)
	};

	// 底面
	DrawLine3D(v[0], v[1], color); DrawLine3D(v[1], v[2], color);
	DrawLine3D(v[2], v[3], color); DrawLine3D(v[3], v[0], color);
	// 上面
	DrawLine3D(v[4], v[5], color); DrawLine3D(v[5], v[6], color);
	DrawLine3D(v[6], v[7], color); DrawLine3D(v[7], v[4], color);
	// 柱
	DrawLine3D(v[0], v[4], color); DrawLine3D(v[1], v[5], color);
	DrawLine3D(v[2], v[6], color); DrawLine3D(v[3], v[7], color);
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