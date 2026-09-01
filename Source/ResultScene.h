#pragma once
#include "Scene.h"

class ResultScene : public Scene
{
public:
	ResultScene() = default;
	~ResultScene() = default;

	void Initialize() override;
	void Update(float _deltaTime) override;
	void Draw() override;
	void Finalize() override;

private:
	int mFontHandle;
};