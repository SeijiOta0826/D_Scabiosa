#pragma once
#include "GameObject.h"

class GoalFlag : public GameObject
{
public:
	GoalFlag() = default;
	~GoalFlag() = default;

	 void Init() override;			
	 void InitComponent() override;
	 void Finalize() override;
	 void Update(float _deltaTime) override;
	 void Draw() override;

	 void ResolvePlayerCollision();

protected:
	const char* GetModelFilename() const override {
		return "Resource/3D/Obj/Goal.mqo";
	}
};