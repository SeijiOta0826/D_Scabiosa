#pragma once
#include "GameObject.h"

#include "Vector3.h"

// キャラクターの共通処理を一元化するクラス
class Character : public GameObject
{
public:
	Character() = default;
	virtual ~Character() = default;

	virtual void Init() override;
	virtual void InitComponent() override;

	virtual void Update(float _deltaTime) override;
	virtual void Draw() override;

	void Move(const Vector3& _direction, float _deltaTime);
	void Attack();
	void TakeDamage(float _damage);

protected:
	virtual const float GetSpeed() const = 0;	// 移動速度
};