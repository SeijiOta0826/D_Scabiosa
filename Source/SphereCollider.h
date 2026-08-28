#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider() = default;
	~SphereCollider() = default;

	const float GetRadius() const { return radius; }
	void SetRadius(const float _radius) { radius = _radius; }

protected:
	const Shape GetShapeType() const override {
		return Shape::Sphere;
	}

private:
	float radius = 1.0f;
};