#pragma once
#include "GameObject.h"

class Character : public GameObject
{
public:
	Character() = default;
	virtual ~Character() = 0;

	virtual void Init() override;
	virtual void InitComponent() override;

	virtual void Update() override;
	virtual void Draw() override;


};