#pragma once

#include <list>
#include <vector>
#include "Object2D.h"
#include "Object3D.h"


//オブジェクトを管理するクラス
class ObjectManager
{
public:
	
	ObjectManager();
	~ObjectManager();

	static ObjectManager& GetInstance();

	void Update(float _deltaTime);	//更新処理	
	void Draw();	//描画処理

public:	//2D関係の関数宣言
	void AddObject(Object2D* Object2D);	//2Dオブジェクト追加
	void DeleteAll2D();	//2Dオブジェクト全削除

	//削除する必要のあるオブジェクトがあれば削除する
	//note: 全てのオブジェクトの更新が終わったあとに呼び出す
	void DeleteAll2DIfNeeded();

	//指定したタグの2Dオブジェクトを取得
	//note: 該当するオブジェクトが複数ある場合、最初に見つけたオブジェクトを返す
	//(一つか)
	Object2D* GetObject2DByTag(Object2D::Tag tag);

	//指定したタグの2Dオブジェクトのリストを取得
	//note: 該当するオブジェクトが複数ある場合、リスト化して全てのオブジェクトを返す
	//(複数あるか)
	std::vector<Object2D*>GetObject2DListByTag(Object2D::Tag tag);

public:
	void AddObject(Object3D* Object3D);	//3Dオブジェクト追加
	void DeleteAll3D();	//3Dオブジェクト全削除

	//削除する必要のあるオブジェクトがあれば削除する
	//note: 全てのオブジェクトの更新が終わったあとに呼び出す
	void DeleteAll3DIfNeeded();

	//指定したタグの3Dオブジェクトを取得
	//note: 該当するオブジェクトが複数ある場合、最初に見つけたオブジェクトを返す
	//(一つか)
	Object3D* GetObject3DByTag(Object3D::Tag3D tag);

	//指定したタグの3Dオブジェクトのリストを取得
	//note: 該当するオブジェクトが複数ある場合、リスト化して全てのオブジェクトを返す
	//(複数あるか)
	std::vector<Object3D*>GetObject3DListByTag(Object3D::Tag3D tag);

private:
	std::list<Object2D*>mObject2DList;	//2Dオブジェクトを管理するリスト
	std::list<Object3D*>mObject3DList;	//3Dオブジェクトを管理するリスト
};


