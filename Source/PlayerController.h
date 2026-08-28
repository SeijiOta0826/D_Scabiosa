#pragma once
#include "Vector3.h"

class Player;

class PlayerController
{
public:
	PlayerController() = default;
	~PlayerController() = default;

	void Init(Player* _player);
	void Update(float _deltaTime);
	
private:
	void UpdateMove(float _deltaTime);
	void UpdateAttack();
	void UpdateJump();
	void UpdateDash();

private:
	Player* mpPlayer;	// Player内にある関数を引っ張るための生ポインタ

	Vector3 mvMoveDirection;
};