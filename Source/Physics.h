#pragma once
#include "DxLib.h"
#include <vector>

class Physics
{
public:
	Physics();
	~Physics();

	VECTOR Update(float _deltaTime);

	void AddForce(const VECTOR& _add) { mForces.push_back(_add); }	//力の追加

private:
	std::vector<VECTOR> mForces;	//あらゆる力のコンテナ

	float mfMass;				//質量
	VECTOR mvVelocity;			//速度
	VECTOR mvAcceleration;		//加速度
};