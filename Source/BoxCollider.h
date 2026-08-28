#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider() = default;
	~BoxCollider() = default;

	const Vector3& GetHalfSize() const { return mvHalfSize; }
	void SetHalfSize(const Vector3& _halfSize) { mvHalfSize = _halfSize; }

protected:
	const Shape GetShapeType() const override {
		return Shape::Box;
	}

private:
	Vector3 mvHalfSize = Vector3(0.5f, 0.5f, 0.5f);
};