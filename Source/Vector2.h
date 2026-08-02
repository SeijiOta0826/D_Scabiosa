#pragma once

class Vector2
{
public:
	float x;
	float y;

public:
	Vector2();
	Vector2(float _x, float _y);
	Vector2(const Vector2& _vector);

	~Vector2() = default;

	Vector2 operator+(const Vector2& _other) const;
	Vector2 operator-(const Vector2& _other) const;
	Vector2 operator*(float value) const;
	Vector2 operator/(float value) const;
	Vector2& operator+=(const Vector2& _other);
	Vector2& operator-=(const Vector2& _other);
	Vector2& operator*=(float value);
	Vector2& operator/=(float value);

	bool operator==(const Vector2& _other) const;
	bool operator!=(const Vector2& _other) const;

	float Length() const;

	Vector2 Normalize() const;

	float Dot(const Vector2& _other) const;
};