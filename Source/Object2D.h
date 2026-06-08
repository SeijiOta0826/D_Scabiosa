#pragma once
#include "DxLib.h"
#include <string>

class Texture;

class Object2D
{
public:

	//2DObjの種類
	enum Tag {
		NONE_2D = 0,
	};

public:
	Object2D(std::string filename,VECTOR initPos);
	virtual ~Object2D();

	virtual void Update();	//更新処理
	virtual void Draw();	//描画処理

	//座標アクセサ
	void SetPosition(VECTOR pos) { mvPosition = pos; }
	VECTOR GetPosition() { return mvPosition; }


	//削除フラグ設定と取得
	void SetDeleteFlag(bool flag) { mbDeleteFlag = flag; }
	bool IsDeleteFlag() { return mbDeleteFlag;}


	//タグの設定と取得
	void SetTag(Tag tag) { mnTag = tag; }
	Tag GetTag() { return mnTag; }


	//画像サイズの取得関数
	int GetSizeX() { return mfsizeX; }
	int GetSizeY() { return mfsizeY; }
	int GetHandle() { return mnHandle; }


	//描画優先度
	void SetZOrder(float z) { mvPosition.z = z; }

	struct CompareZOrder {
		bool operator()(Object2D* a, Object2D* b)
			const {
			return a->GetPosition().z < b->GetPosition().z;
		}
	};

protected:
	Texture* mpTexture;	//画像データ
	VECTOR mvPosition;	//2DObjとしての座標

	float mfsizeX;	//画像のサイズ(X)
	float mfsizeY;	//画像のサイズ(Y)
	int mnHandle;	//テクスチャーのハンドルデータ

private:
	Tag mnTag;	//2DObjに付与されるタグを示す
	bool mbDeleteFlag;//削除フラグ
};

