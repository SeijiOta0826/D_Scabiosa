#include "AttachmentModel.h"


AttachmentModel::AttachmentModel(std::string filename, int parentModelHandle, int parentFrameIndex)
	//座標はアタッチ先によって変わるので初期値は0
	:Object3D(VGet(0.0f,0.0f,0.0f))
	, mnParentHandle(parentModelHandle)
	, mnParentFrameIndex(parentFrameIndex)
{
	//3Dモデルの読み込み
	mnHandle = MV1LoadModel(filename.c_str());
}

AttachmentModel::~AttachmentModel()
{
	//3Dモデルの破棄
	MV1DeleteModel(mnHandle);
}

void AttachmentModel::Update()
{
	//アタッチ先のモデルのフレームの行列情報を取得
	MATRIX matrix = MV1GetFrameLocalWorldMatrix(mnParentHandle, mnParentFrameIndex);

	//上で取得した行列情報を自身に設定する
	MV1SetMatrix(mnHandle, matrix);
}

void AttachmentModel::Draw()
{
	//モデルの描画
	MV1DrawModel(mnHandle);

}

