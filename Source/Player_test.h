#pragma once
#include "GameObject.h"

class Player_test : public GameObject
{
public:
	Player_test() = default;
	virtual~Player_test() = default;

	virtual void Init() override;
	virtual void InitComponent() override;

	virtual void Update() override;
	virtual void Draw() override;
};