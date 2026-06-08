#pragma once
#include "DxLib.h"
#include <string>


class Object3D
{
public:
	//3Dobjの種類を示す
	enum Tag3D{
		None3D = 0,		//設定なし
	};

public:
	
	Object3D(VECTOR initPos);
	virtual ~Object3D();

	virtual void Update();	//更新処理
	virtual void Draw();	//描画処理

	//座標アクセサ
	void SetPosition(VECTOR pos) {mvPosition = pos;}
	VECTOR GetPosition() { return mvPosition; }

	//回転アクセサ
	void SetRotatio(VECTOR rot) { mvRotation = rot; }
	VECTOR GetRotation() { return mvRotation; }

	//削除フラグアクセサ
	void SetDeleteFlag(bool flag) { mbDeleteFlag = flag; }
	bool IsDeleteFlag() { return mbDeleteFlag; }

	//タグアクセサ
	void SetTag(Tag3D tag) { mnTag = tag;}
	Tag3D GetTag() { return mnTag; }


protected:
	VECTOR mvPosition;	//座標
	VECTOR mvRotation;	//回転

private:
	Tag3D mnTag;	//3DObjの種類を示す
	bool mbDeleteFlag;	//削除する必要があるかどうかを示す
};