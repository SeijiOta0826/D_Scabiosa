#pragma once
#include <vector>
#include <memory>
#include <utility>
#include <string>

class Component;
class ObjectManager;

// コンポーネントを保持・管理するゲームオブジェクトの基底クラス
class GameObject
{
public:
	virtual ~GameObject() = default;

	virtual void Init() = 0;			// 初期化処理
	virtual void InitComponent() = 0;	// コンポーネント初期設定
	virtual void Update(float _deltaTime);		// 保有するコンポーネントの更新処理
	virtual void Draw();		// 保有するコンポーネントの描画処理

	// 自身にコンポーネントを追加する
	template <class T,class...Args>
	T* AddComponent(Args&&...args) {
		static_assert(std::is_base_of_v<Component, T>,
			"T must derive from Component.");

		auto component = std::make_unique<T>(std::forward<Args>(args)...);

		component->mpGameObject = this;
		T* ptr = component.get();

		mComponents.push_back(std::move(component));

		return ptr;
	}

	// 自身に付与されている指定コンポーネントを取得
	template<class T>
	T* GetComponent() {
		for (auto& component : mComponents) {
			if (auto ptr = dynamic_cast<T*>(component.get())) return ptr;
		}

		return nullptr;
	}

	// 同Scene内のObjectManagerへのゲッター
	ObjectManager* GetObjectManager() { return mpObjectManager; }

	// 解放するかどうかのフラグアクセサ
	void Destroy() { mbDestroy = true; }
	bool IsDestroy() { return mbDestroy; }

	void SetTag(const std::string& _tag) { msTag = _tag; }
	const std::string& GetTag() const { return msTag; }

protected:
	virtual const char* GetModelFilename() const = 0;

private:
	friend class ObjectManager;
	ObjectManager* mpObjectManager;
	void Initialize(ObjectManager* _manager);

private:
	std::vector<std::unique_ptr<Component>> mComponents;	//所持しているコンポーネントのコンテナ

private:
	bool mbDestroy = false;
	std::string msTag;
};