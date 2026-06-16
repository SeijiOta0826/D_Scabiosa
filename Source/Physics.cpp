#include "Physics.h"

Physics::Physics() {

}

Physics::~Physics() {

}

VECTOR Physics::Update(float _deltaTime) {

	VECTOR vForce = VGet(0.0f, 0.0f, 0.0f);	//最終的に適用される移動量

	float fResistance = 10.0f;	//抵抗力(仮)

	for (auto force = mForces.begin();
		force != mForces.end();) {

		vForce = VAdd(vForce, (*force));
		//抵抗力を算出
		VECTOR vDrag =
			VScale(VNorm(*force), fResistance);

		*force = VSub(*force, vDrag);	//抵抗を履行

		if (VSize((*force)) <= fResistance) {
			force = mForces.erase(force);
		}
		else {
			force++;
		}
	}

	return vForce;
}