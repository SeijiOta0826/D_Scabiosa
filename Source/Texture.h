#pragma once
#include "DxLib.h"
#include <string>
#include "Vector3.h"

class Texture
{
public:
	Texture(std::string filename, Vector3 centerPosition, int trandFlag);
	~Texture();

	void Update();
	void Draw();

	// 座標のアクセサ
	void SetPosition(Vector3 centerPosition) { mvPosition = centerPosition; }
	Vector3 GetPosition() { return mvPosition; }

	int GetSizeX() { return mnSizeX; }	// サイズ取得(X)
	int GetSizeY() { return mnSizeY; }	// サイズ取得(Y)

	int GetHandle() { return mnHandle; }	// ハンドルの取得関数

private:
	int mnHandle;		// 読み込んだ画像のハンドル

	Vector3 mvPosition;	// 座標
	int mnSizeX;		// 画像の幅
	int mnSizeY;		// 画像の高さ
	int mnTransFlag;	// 透過を有効にするかどうかを示す
};
