#pragma once

class Component
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();

	virtual void OnEnable();
	virtual void OnDisable();

	bool IsEnabled() const{return }

	pro
};