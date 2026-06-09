#pragma once
#include "Object3D.h"

class Model;

class Player : public Object3D
{
public:
	Player();
	~Player();

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	Model* mpModel;	//モデルデータ
};