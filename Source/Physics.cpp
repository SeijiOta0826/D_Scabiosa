#include "Physics.h"

Physics::Physics() {

}

Physics::~Physics() {

}

VECTOR Physics::Update(float _deltaTime) {
	VECTOR vMove = VGet(0.0f, 0.0f, 0.0f);	//運動量を移動量に変換した値

	VECTOR vTotalForce = VGet(0.0f, 0.0f, 0.0f);	//受け取った運動要素の合計
	for (const auto& force : mForces) {
		vTotalForce = VAdd(vTotalForce, force);	//合算
	}

	//F = ma
	VECTOR vAcceleration =
		VScale(vTotalForce, 1.0f / mfMass);

	//v = at
	mvVelocity = VAdd(mvVelocity,vAcceleration);

	vMove = mvVelocity;
	mvVelocity = VScale(mvVelocity, 0.95f);	//速度減衰

	mForces.clear();
	return vMove;
}