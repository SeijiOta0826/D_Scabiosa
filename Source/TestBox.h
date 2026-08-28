#pragma once
#include "GameObject.h"

class TestBox : public GameObject
{
public:
	TestBox() = default;
	~TestBox() = default;

	void Init() override;
	void InitComponent() override;
	void Finalize() override;
	void Update(float _deltaTime) override;
	void Draw() override;

protected:
	const char* GetModelFilename() const override {
		return "Resource/3D/Obj/TestBox.mqo";
	}
};