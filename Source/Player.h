#pragma once
#include "Character.h"

#include "Vector3.h"
#include <string>

#include "PlayerController.h"

class Player : public Character
{
public:
	Player() = default;
	virtual~Player() = default;

	virtual void Init() override;
	virtual void InitComponent() override;

	virtual void Update(float _deltaTime) override;
	virtual void Draw() override;

	void RotationByMove();

	std::string DetermineAnimationState();	//アニメーション状態の決定ロジックに従い、遷移先アニメーションを決定する
	void UpdateAnimation();

	void ResolveWallCollision();	// 壁との衝突による移動制限を行う
protected:
	const char* GetModelFilename() const override {
		return "Resource/3D/Character/Paladin/Mesh.mv1";
	}

	const float GetWalkSpeed() const override{
		return WALK_SPEED;
	}
	const float GetRunSpeed() const override {
		return RUN_SPEED;
	}

private:
	PlayerController mController;

	static constexpr float WALK_SPEED = 1000.0f;		//歩き時の限界速度
	static constexpr float RUN_SPEED = 2000.0f;		//走り時の限界速度
	float mfAngle = 0.0f;							//現在の角度
	float mfTargetAngle = 0.0f;						//目標の角度
	static constexpr float ROTATE_SPEED = 0.2f;		//回転速度

};