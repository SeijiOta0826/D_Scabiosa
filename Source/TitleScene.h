#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	TitleScene() = default;
	~TitleScene() = default;

	void Initialize() override;
	void Update(float _deltaTime) override;
	void Draw() override;
	void Finalize() override;

private:
	int mFontHandle;
};