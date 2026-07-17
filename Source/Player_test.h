#pragma once
#include "GameObject.h"

#include "Vector3.h"
#include <string>


class Player_test : public GameObject
{
public:
	Player_test() = default;
	virtual~Player_test() = default;

	virtual void Init() override;
	virtual void InitComponent() override;

	virtual void Update() override;
	virtual void Draw() override;

	void Move();
	void RotationByMove();
	void UpdateMovePower(const Vector3& _move, bool _isRunning);	//移動速度

	const std::string& DetermineAnimationState();	//アニメーション状態の決定ロジックに従い、遷移先アニメーションを決定する
	void UpdateAnimation();

private:
	static constexpr float WALK_SPEED = 1.0f;		//歩き時の限界速度
	static constexpr float RUN_SPEED = 2.0f;		//走り時の限界速度
	float mfCurrentSpeed = 0.0f;					//現在の速度
	float mfTargetSpeed = 0.0f;						//目標の速度
	float mfAngle = 0.0f;							//現在の角度
	float mfTargetAngle = 0.0f;						//目標の角度
	static constexpr float ROTATE_SPEED = 0.2f;		//回転速度

};