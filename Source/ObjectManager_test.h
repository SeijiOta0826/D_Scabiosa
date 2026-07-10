#pragma once
#include <memory>
#include <vector>

class GameObject;

class ObjectManager_test
{
public:
	enum class ObjTag
	{
		OBJ_NONE = 0,
		OBJ_PLAYER,
	};
public:
	ObjectManager_test();
	~ObjectManager_test();

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

	void FindObject(ObjTag _tag);	//w’èObj‚Ì’Tõ
	void FindObjects(ObjTag _tag);	//w’è•¡”Obj

private:
	std::vector<std::unique_ptr<GameObject>> mObjects;
	
};