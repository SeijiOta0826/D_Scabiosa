#include "ModelRenderer.h"

#include "DxLib.h"
#include "GameObject.h"
#include "Transform .h"

ModelRenderer::ModelRenderer(const char* _filename) {
	mnModelHandle = MV1LoadModel(_filename);
}

void ModelRenderer::Init() {

}

// 描画する座標,角度を更新
void ModelRenderer::Update() {
	auto* transform = mpGameObject->GetComponent<Transform>();

	if (!transform) return;

	MV1SetPosition(mnModelHandle, transform->GetPosition().ToDxVector());		//座標設定
	MV1SetRotationXYZ(mnModelHandle, transform->GetRotation().ToDxVector());	//回転設定
}

// モデルを描画
void ModelRenderer::Draw() {
	MV1DrawModel(mnModelHandle);
}