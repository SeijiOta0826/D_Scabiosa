#pragma once
#include "Component.h"

class ModelRenderer : public Component
{
public:
	ModelRenderer(const char* _filename);
	void Init() override;			// 初期化処理
	void Update() override;			// 描画する座標,角度を更新
	void Draw() override;			// モデルを描画

	int GetModelHandle() const { return mnModelHandle; }		// モデルハンドルの取得

private:
	int mnModelHandle = -1;	//モデルハンドル
};