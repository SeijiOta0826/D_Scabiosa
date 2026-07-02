#pragma once
#include <vector>
#include <memory>

class Component;

class GameObject
{
public:
	virtual ~GameObject() = default;

	virtual void Init() = 0;
	virtual void Update();
	virtual void Draw();

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

private:
	std::vector<std::unique_ptr<Component>> mComponents;	//所持しているコンポーネントのコンテナ
};