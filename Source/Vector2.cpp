#include "Vector2.h"
#include <cmath>

Vector2::Vector2()
	:x(0.0f)
	, y(0.0f) {
}

Vector2::Vector2(float _x, float _y)
	:x(_x)
	, y(_y) {
}

Vector2::Vector2(const Vector2& _vector)
	:x(_vector.x)
	, y(_vector.y) {
}

Vector2 Vector2::operator+(const Vector2& _other) const {
	return Vector2(
		x + _other.x,
		y + _other.y
	);
}

Vector2 Vector2::operator-(const Vector2& _other) const {
	return Vector2(
		x - _other.x,
		y - _other.y
	);
}

Vector2 Vector2::operator*(float value) const {
	return Vector2(
		x * value,
		y * value
	);
}

Vector2 Vector2::operator/(float value) const {
	return Vector2(
		x / value,
		y / value
	);
}

Vector2& Vector2::operator+=(const Vector2& _other) {
	x += _other.x;
	y += _other.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& _other) {
	x -= _other.x;
	y -= _other.y;

	return *this;
}

Vector2& Vector2::operator*=(float value) {
	x *= value;
	y *= value;

	return *this;
}

Vector2& Vector2::operator/=(float value) {
	x /= value;
	y /= value;

	return *this;
}

bool Vector2::operator==(const Vector2& _other) const {
	return
		x == _other.x &&
		y == _other.y;
}

bool Vector2::operator!=(const Vector2& _other) const {
	return
		x != _other.x ||
		y != _other.y;
}

float Vector2::Length() const {
	return sqrtf(
		x * x +
		y * y
	);
}

Vector2 Vector2::Normalize() const {
	float fLength = this->Length();	//長さを取得

	if (fLength == 0.0f) return Vector2();	// 長さ0のベクトルは正規化できないためゼロベクトルを返す

	return Vector2(
		x / fLength,
		y / fLength
	);
}

float Vector2::Dot(const Vector2& _other) const {
	return
		x * _other.x +
		y * _other.y;
}

