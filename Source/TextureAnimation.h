#pragma once
#include "DxLib.h"
#include "Object2D.h" 
#include <string>

class TextureAnimation:public Object2D
{
public:
	//コンストラクタ
	TextureAnimation(
		VECTOR position,		//場所
		std::string filename,	//ファイル名
		int allNum,				//分割数
		int xNum,				//横の数
		int yNum,				//縦の数
		int interval			//フレーム数clas
		);
	//デストラクタ
	~TextureAnimation();


	void Update();	//更新

	void Draw();	//描画

	int Counter()
	{
		return mnCounter;
	}

private:

	VECTOR mvPosition;	//ポジション

	int mnCounter;	//あにめーしょんカウンター
	int mnInterval;	//テクスチャ切り替えのフレーム数
	int mnCurrentNum;	//何番目のテクスチャを表示するか
	int* mnHandleList;	//分割されたテクスチャのハンドルリスト
	int mnAllNum;		//テクスチャ分割数
};

