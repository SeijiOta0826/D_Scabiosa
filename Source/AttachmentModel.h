#pragma once
#include"DxLib.h"
#include"Object3D.h"

class AttachmentModel : public Object3D
{
public:

	//ぞれぞれ
	//ファイル名、くっついたモデルのハンドル、くっついたモデルのフレーム番号
	AttachmentModel(std::string filename,int parentModelHandle,int parentFrameIndex);

	~AttachmentModel();

	void Update() override;

	void Draw() override;

	//モデルハンドルの取得
	int GetHandle() { return mnHandle; }

private:


	//モデルハンドル
	int mnHandle;
	//親モデルのハンドル
	int mnParentHandle;
	//親モデルのフレーム番号
	int mnParentFrameIndex;


	//くっつけたい先のモデルは親モデルとか、反対は子モデルとかいう

};
