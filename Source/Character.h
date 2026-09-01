#pragma once
#include "GameObject.h"

#include "Vector3.h"
#include "Vector2.h"

// キャラクターの共通処理を一元化するクラス
class Character : public GameObject
{
public:
	Character() = default;
	virtual ~Character() = default;

	virtual void Init() override;
	virtual void InitComponent() override;

	virtual void Finalize() override;

	virtual void Update(float _deltaTime) override;
	virtual void Draw() override;

	void Move(const Vector3& _direction, float _deltaTime);
	void RotateTo(const Vector3& _direction);
	void Attack(Character* _target);
	void TakeDamage(float _damage);
	bool IsInAttackRange(Character* _target);

	void SetSpeed(float _speed) { mfCurrentSpeed = _speed; }
	float GetSpeed() { return mfCurrentSpeed; }

	void SetIsRunning(float _flag) { mbIsRunning = _flag; }
	float GetIsRunning() { return mbIsRunning; }

	void UpdateMovePower(const Vector2& _move, bool _isRunning);

protected:
	virtual const float GetWalkSpeed() const = 0;
	virtual const float GetRunSpeed() const = 0;

private:
	float mfCurrentSpeed = 0.0f;
	float mfTargetSpeed = 0.0f;

	bool mbIsRunning = false;
	float mfAttackRange = 100.0f;
};