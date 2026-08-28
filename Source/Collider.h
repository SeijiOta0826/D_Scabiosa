#pragma once
#include "Component.h"
#include "Vector3.h"

#include <string>
#include <vector>
#include <variant>

#include "CollisionManager.h"

class GameObject;
class CollisionManager;

class Collider : public Component
{
public:
	Collider() = default;
	virtual ~Collider() = default;

	virtual void Initialize() override;	// 初期処理
	virtual void Finalize() override;	// 終了処理

	// Objの位置(Transform)からの相対オフセット位置アクセサ
	void SetOffset(const Vector3& _offset) { mvOffSetPos = _offset; }
	const Vector3& GetOffset() const { return mvOffSetPos; }
	
	Vector3 GetWorldPosition() const;	// Collider中心座標(Transform + Offset)を返す

	bool IsColliding() const;							// 何かしらに当たったら反応
	bool IsColliding(const std::string& _tag) const;	// 指定タグのColliderに衝突時、反応
	GameObject* GetCollision(const std::string& _tag) const;	// 指定タグの衝突したGameObjectを返す

protected:
	virtual const Shape GetShapeType() const = 0;

private:
	friend class CollisionManager;

	void AddCollision(Collider* _collider) { mCollisions.push_back(_collider); }
	void ClearCollisions() { mCollisions.clear(); }

private:
	Vector3 mvOffSetPos;	// Objの位置(Transform)からの相対オフセット位置

	std::vector<Collider*> mCollisions;
};