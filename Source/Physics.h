#pragma once
#include "Vector3.h"
#include <vector>

class Physics
{
public:
	Physics();
	~Physics();

	//受けている全運動を座標移動の値に変換する
	Vector3 Update(float _deltaTime);

	void AddForce(const Vector3& _add) { mForces.push_back(_add); }	//力の追加

private:
	std::vector<Vector3> mForces;	//受け取った運動量のコンテナ

	float mfMass = 1.0f;				//質量
	Vector3 mvVelocity;			//速度
};