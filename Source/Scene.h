#pragma once
#include <memory>

class ObjectManager;

class Scene
{
public:

	Scene();
	~Scene() = default;

	virtual void Initialize() = 0;	//‰Šú‰»ˆ—

	virtual void Update(float _deltaTime);	//XVˆ—
	virtual void Draw();	//•`‰æˆ—

	virtual void Finalize() = 0;	//I—¹ˆ—

protected:
	std::unique_ptr<ObjectManager> mpObjectManager;
};
