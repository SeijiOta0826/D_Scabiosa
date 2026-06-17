#pragma once
#include "Object3D.h"
#include <memory>

class Model;
class Physics;

class Player : public Object3D
{
public:
	Player();
	~Player();

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	Model* mpModel;	//モデルデータ
	std::unique_ptr<Physics> mpPhysics;
};