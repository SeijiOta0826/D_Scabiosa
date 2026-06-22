#include "Physics.h"

Physics::Physics() {

}

Physics::~Physics() {

}

Vector3 Physics::Update(float _deltaTime) {
	Vector3 vMove;	//運動量を移動量に変換した値

	Vector3 vTotalForce;	//受け取った運動要素の合計
	for (const auto& force : mForces) {
		vTotalForce = vTotalForce + force;	//合算
	}

	//F = ma
	Vector3 vAcceleration =
		vTotalForce * (1.0f / mfMass);

	//v = at
	mvVelocity = mvVelocity + vAcceleration;

	vMove = mvVelocity;
	mvVelocity = mvVelocity * 0.95f;	//速度減衰

	mForces.clear();
	return vMove;
}