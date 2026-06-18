#include "Vector3.h"

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
