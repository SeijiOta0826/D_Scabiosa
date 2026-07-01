#pragma once
#include <memory>

// 
class Component
{
public:
	virtual ~Component() = default;

	virtual void Init();		//初期化処理
	virtual void Update();		//更新処理
	virtual void Draw();		//描画処理

	// コンポーネントが有効であるかどうかのアクセサ
	bool IsEnabled() const { return mbEnabled; }
	void SetEnabled(bool _enabled) { mbEnabled = _enabled; }

protected:
	//Todo : GameObjectのクラスポインターを宣言しておく

private:
	//friend class :  GameObjectを設定する
	bool mbEnabled = true;		// trueならUpdate・Drawなどの処理を行う
};