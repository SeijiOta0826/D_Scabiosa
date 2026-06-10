#include "DxLib.h"
#include "TextureAnimation.h"

//コンストラクタ
TextureAnimation::TextureAnimation(
	VECTOR position,		//場所
	std::string filename,	//ファイル名
	int allNum,				//分割数
	int xNum,				//横の数
	int yNum,				//縦の数
	int interval			//
	)
	:Object2D(filename,position)
	,mvPosition(position)
	,mnCounter(0)
	,mnInterval(interval)
	,mnAllNum(allNum)
{
	mnHandleList = new int[allNum];

	int handle = LoadGraph(filename.c_str());

	if (handle == -1)
	{
		return;
	}

	//サイズ取得
	int sizeX, sizeY;
	GetGraphSize(handle, &sizeX, &sizeY);

	int success = LoadDivGraph(
		filename.c_str(),
		allNum,
		xNum,
		yNum,
		sizeX / xNum,
		sizeY / yNum,
		mnHandleList
	);


	if (success == -1)
	{
		return;
	}
}

TextureAnimation::~TextureAnimation()
{

}

void TextureAnimation::Update()	//更新
{
	//カウンタをインクリメント
	mnCounter++;

	if (mnCounter % mnInterval == 0)
	{
		mnCurrentNum++;//テクスチャ番号を決める
		
		if (mnCurrentNum >= mnAllNum)	//分割数を超えるならループする
		{
			SetDeleteFlag(true);

			return;
		}
	}
}


void TextureAnimation::Draw()//描画
{
	DrawGraph(mvPosition.x,mvPosition.y,mnHandleList[mnCurrentNum],true);
}