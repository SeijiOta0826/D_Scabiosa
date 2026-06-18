#pragma once

class Vector3
{
public:
	float x;
	float y;
	float z;

public:
	Vector3();
	Vector3(float _x, float _y, float _z);

	~Vector3() = default;

	Vector3 operator+(const Vector3& _other) const;
	Vector3 operator-(const Vector3& _other) const;
	Vector3 operator*(float value) const;
	Vector3 operator/(float value) const;
	Vector3& operator+=(const Vector3& _other);
	Vector3& operator-=(const Vector3& _other);
	Vector3& operator*=(float value);
	Vector3& operator/=(float value);
	Vector3 operator==(const Vector3& _other) const;
	Vector3 operator!=(const Vector3& _other) const;
};