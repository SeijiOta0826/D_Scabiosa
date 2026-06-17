#include "Physics.h"

Physics::Physics() {

}

Physics::~Physics() {

}

VECTOR Physics::Update(float _deltaTime) {
	VECTOR vTotalForce = VGet(0.0f, 0.0f, 0.0f);	//受け取った運動要素の合計
	for (const auto& force : mForces) {
		vTotalForce = VAdd(vTotalForce, force);	//合算
	}

	//F = ma
	VECTOR vAcceleration =
		VScale(vTotalForce, 1.0f / mfMass);

	//v = at
	mvVelocity = VAdd(mvVelocity,vAcceleration);

	VECTOR move = mvVelocity;
	mvVelocity = VScale(mvVelocity, 0.95f);	//速度減衰

	return move;
}