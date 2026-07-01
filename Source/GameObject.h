#pragma once
#include <memory>

class GameObject
{
public:
	virtual ~GameObject() = default;

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	template <class T,class...Args>
	T* AddComponent(Args&&...args);

	template<class T>
	T* GetComponent();

private:
	std::unique_ptr<GameObject> mComponents;	//所持しているコンポーネントのコンテナ
};