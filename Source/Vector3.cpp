#include "Vector3.h"
#include <math.h>

Vector3::Vector3()
	:x(0.0f)
	, y(0.0f)
	, z(0.0f) {

}

Vector3::Vector3(float _x, float _y, float _z)
	:x(_x)
	, y(_y)
	, z(_z) {

}

Vector3 Vector3::operator+(const Vector3& _other) const {
	return Vector3(
		x + _other.x,
		y + _other.y,
		z + _other.z
	);
}

Vector3 Vector3::operator-(const Vector3& _other) const {
	return Vector3(
		x - _other.x,
		y - _other.y,
		z - _other.z
	);
}

Vector3 Vector3::operator*(float value) const {
	return Vector3(
		x * value,
		y * value,
		z * value
	);
}

Vector3 Vector3::operator/(float value) const {
	return Vector3(
		x / value,
		y / value,
		z / value
	);
}

Vector3& Vector3::operator+=(const Vector3& _other) {
	x += _other.x;
	y += _other.y;
	z += _other.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& _other) {
	x -= _other.x;
	y -= _other.y;
	z -= _other.z;

	return *this;
}

Vector3& Vector3::operator*=(float value) {
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

Vector3& Vector3::operator/=(float value) {
	x /= value;
	y /= value;
	z /= value;

	return *this;
}

float Vector3::Length() const {
	return sqrtf(
		x * x +
		y * y +
		z * z
	);
}

Vector3 Vector3::Normalize() const {
	float fLength = this->Length();	//長さを取得

	if (fLength == 0.0f) return Vector3();	// 長さ0のベクトルは正規化できないためゼロベクトルを返す

	return Vector3(
		x / fLength,
		y / fLength,
		z / fLength
	);
}

float Vector3::Dot(const Vector3& _other) const {
	return
		x * _other.x +
		y * _other.y +
		z * _other.z;
}

Vector3 Vector3::Cross(const Vector3& other) const {
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}


