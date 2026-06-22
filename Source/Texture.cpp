#include "Texture.h"

Texture::Texture(std::string filename, Vector3 centerPosition, int transFlag)
	: mnHandle(-1)
	, mvPosition(centerPosition)
	, mnSizeX(0)
	, mnSizeY(0)
	, mnTransFlag(transFlag) {

	mnHandle = LoadGraph(filename.c_str());	// 画像の読み込み
	GetGraphSize(mnHandle, &mnSizeX, &mnSizeY);	// 画像のサイズを取得する
}

Texture::~Texture(){
	DeleteGraph(mnHandle);	// 読み込んだ画像の破棄
}

void Texture::Draw(){
	DrawGraph(mvPosition.x - (mnSizeX / 2), mvPosition.y - (mnSizeY / 2), mnHandle, mnTransFlag);	// 画像の描画
}

void Texture::Update(){

}