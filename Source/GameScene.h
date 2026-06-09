#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void Initialize() override;
	void Update(float _deltaTime) override;
	void Draw() override;
	void Finalize() override;

	void DebagDraw();

private:

};