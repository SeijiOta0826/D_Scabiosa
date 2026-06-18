#pragma once
#include "DxLib.h"
#include <vector>

class Physics
{
public:
	Physics();
	~Physics();

	//受けている全運動を座標移動の値に変換する
	VECTOR Update(float _deltaTime);

	void AddForce(const VECTOR& _add) { mForces.push_back(_add); }	//力の追加

private:
	std::vector<VECTOR> mForces;	//受け取った運動量のコンテナ

	float mfMass = 1.0f;				//質量
	VECTOR mvVelocity;			//速度
};