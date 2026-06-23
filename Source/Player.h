#pragma once
#include "Object3D.h"
#include <memory>
#include "ModelUtility.h"

class Model;
class Physics;

class Player : public Object3D
{
public:
	Player();
	~Player();

	void Update(float _deltaTime) override;
	void Draw() override;

	void Move();	//移動処理

	void AddAnimation(AnimationState state, std::string filename);	// アニメーション追加(Modelへの橋渡し)

private:
	std::unique_ptr<Model> mpModel;			//モデルデータ
	std::unique_ptr<Physics> mpPhysics;		//物理データ
};