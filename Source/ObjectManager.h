#pragma once
#include <memory>
#include <vector>

#include "GameObject.h"


class ObjectManager
{
public:
	ObjectManager() = default;
	~ObjectManager() = default;

	void Initialize();
	void Finalize();

	void Update(float _deltaTime);
	void Draw();

	template <class T,class...Args>
	T* CreateObject(Args&&... args) {
		static_assert(
			std::is_base_of_v<GameObject, T>,
			"T must derive from GameObject"
			);

		auto obj = std::make_unique<T>(std::forward<Args>(args)...);

		obj->Initialize(this);

		T* ptr = obj.get();
		mObjects.push_back(std::move(obj));
		
		return ptr;
	}

	template<class T>
	T* FindObject() {
		for (auto& object : mObjects) {
			if (auto ptr = dynamic_cast<T*>(object.get())) {
				return ptr;
			}
		}

		return nullptr;
	}

	template<class T>
	std::vector<T*> FindObjects() {
		static_assert(
			std::is_base_of_v<GameObject, T>,
			"T must derive from GameObject"
			);

		std::vector<T*> result;

		for (auto& object : mObjects) {
			if (auto ptr = dynamic_cast<T*>(object.get())) {
				result.push_back(ptr);
			}
		}

		return result;
	}

	void Clear();	// 全てのObjectを解放する(シーン終了時など)

private:
	void RemoveDestroyObjects();

private:
	std::vector<std::unique_ptr<GameObject>> mObjects;
	
};