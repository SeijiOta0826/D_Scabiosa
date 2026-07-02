#pragma once
#include <memory>

class GameObject;

// GameObjectに追加して機能を拡張するコンポーネントの基底クラス 
class Component
{
public:
	virtual ~Component() = default;

	virtual void Init() = 0;		//初期化処理
	virtual void Update() = 0;		//更新処理
	virtual void Draw() = 0;		//描画処理

	// コンポーネントが有効であるかどうかのアクセサ
	bool IsEnabled() const { return mbEnabled; }
	void SetEnabled(bool _enabled) { mbEnabled = _enabled; }

protected:
	std::unique_ptr<GameObject> mpGameObject;	// このコンポーネントを所持するGameObject

private:
	friend class GameObject;	// コンポーネント追加時に所有元GameObjectを設定するため
	bool mbEnabled = true;		// trueならUpdate・Drawなどの処理を行う
};