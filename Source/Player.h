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

	void Move();								//移動処理
	void RotationByMove();						//回転処理
	void UpdateMovePower(const Vector3& _move, bool _isRunning);	//移動速度
		
	void AddAnimation(AnimationState state,const std::string& filename);	// アニメーション追加(Modelへの橋渡し)
	AnimationState DetermineAnimationState();						//アニメーション状態の決定ロジックに従い、遷移先アニメーションを決定する
	void UpdateAnimation();

	void Attack();	//攻撃処理
	

private:
	std::unique_ptr<Model> mpModel;			//モデルデータ
	std::unique_ptr<Physics> mpPhysics;		//物理データ

	static constexpr float WALK_SPEED = 1.0f;		//歩き時の限界速度
	static constexpr float RUN_SPEED = 2.0f;		//走り時の限界速度
	float mfCurrentSpeed = 0.0f;					//現在の速度
	float mfTargetSpeed = 0.0f;						//目標の速度
	float mfAngle = 0.0f;							//現在の角度
	float mfTargetAngle = 0.0f;						//目標の角度
	static constexpr float ROTATE_SPEED = 0.2f;		//回転速度

};