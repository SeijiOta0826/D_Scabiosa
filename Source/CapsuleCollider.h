#pragma once
#include "Collider.h"

class CapsuleCollider : public Collider
{
public:
	CapsuleCollider() = default;
	~CapsuleCollider() = default;

	const Vector3& GetStart() const { return mvStart; }
	void SetStart(const Vector3& _start) { mvStart = _start; }

	const Vector3& GetEnd() const { return mvEnd; }
	void SetEnd(const Vector3& _end) { mvEnd = _end; }

	const float GetRadius() const{ return mfRadius; }
	void SetRadius(float _radius) { mfRadius = _radius; }

protected:
	const Shape GetShapeType() const override {
		return Shape::Capsule;
	}

private:
	Vector3 mvStart;
	Vector3 mvEnd;
	float mfRadius = 0.5f;
};