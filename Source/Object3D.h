#pragma once
#include "DxLib.h"
#include <string>
#include "Vector3.h"

class Object3D
{
public:
	//3Dobjの種類を示す
	enum Tag3D {
		None3D = 0,		//設定なし

		OBJ_PLAYER,		//プレイヤー
	};

public:
	
	Object3D(Vector3 initPos);
	virtual ~Object3D();

	virtual void Update(float _deltaTime);	//更新処理
	virtual void Draw();	//描画処理

	//座標アクセサ
	void SetPosition(Vector3 pos) {mvPosition = pos;}
	Vector3 GetPosition() { return mvPosition; }

	//回転アクセサ
	void SetRotatio(Vector3 rot) { mvRotation = rot; }
	Vector3 GetRotation() { return mvRotation; }

	//削除フラグアクセサ
	void SetDeleteFlag(bool flag) { mbDeleteFlag = flag; }
	bool IsDeleteFlag() { return mbDeleteFlag; }

	//タグアクセサ
	void SetTag(Tag3D tag) { mnTag = tag;}
	Tag3D GetTag() { return mnTag; }


protected:
	Vector3 mvPosition;	//座標
	Vector3 mvRotation;	//回転

private:
	Tag3D mnTag;	//3DObjの種類を示す
	bool mbDeleteFlag;	//削除する必要があるかどうかを示す
};