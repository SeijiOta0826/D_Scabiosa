#include "ObjectManager.h"

ObjectManager::ObjectManager(){

}

ObjectManager::~ObjectManager(){

}

//更新処理
void ObjectManager::Update(float _deltaTime)
{
	for (std::list<Object2D*>::iterator itr = mObject2DList.begin();
		itr != mObject2DList.end();
		itr++) {
		(*itr)->Update();
	}

	for (std::list<Object3D*>::iterator itr = mObject3DList.begin();
		itr != mObject3DList.end();
		itr++) {
		(*itr)->Update(_deltaTime);
	}
}

//描画処理
void ObjectManager::Draw() {
	mObject2DList.sort(Object2D::CompareZOrder());	//Zオーダーを利用したソートをしておく

	for (auto itr = mObject2DList.begin();
		itr != mObject2DList.end();
		itr++) {
		(*itr)->Draw();
	}

	for (auto itr = mObject3DList.begin();
		itr != mObject3DList.end();
		itr++) {
		(*itr)->Draw();
	}
}


// --2D-- //
//2Dオブジェクトの追加
void ObjectManager::AddObject(Object2D* object2D) {
	mObject2DList.push_back(object2D);
}

//2Dオブジェクトの全削除
void ObjectManager::DeleteAll2D() {
	for (auto itr = mObject2DList.begin();
		itr != mObject2DList.end();) {
		Object2D* temp = *itr;	//コンテナ内のアドレスをローカルへ一時避難

		itr = mObject2DList.erase(itr);	//リストから削除

		delete temp;	//ローカルのデータを解放
		temp = nullptr;	//一応null
	}
}

void ObjectManager::DeleteAll2DIfNeeded() {
	for (auto itr = mObject2DList.begin();
		itr != mObject2DList.end();) {

		//削除フラグの立っているObjの場合
		if ((*itr)->IsDeleteFlag()) {
			Object2D* temp = *itr;	//コンテナ内のアドレスをローカルへ一時避難

			itr = mObject2DList.erase(itr);	//リストから削除

			delete temp;	//ローカルのデータを解放
			temp = nullptr;	//一応null
		}

		//削除フラグの立っていないObjの場合
		else{
			itr++;	//そのまま通過。要素を進める
		}
	}
}

//指定したタグの2Dオブジェクトを取得
Object2D* ObjectManager::GetObject2DByTag(Object2D::Tag tag){
	auto itr = std::find_if(
		mObject2DList.begin(),	
		mObject2DList.end(),	
		[&](Object2D* obj) {return obj->GetTag() == tag; }
	);

	//オブジェクトが見つかった場合
	if (itr != mObject2DList.end()){
		return (*itr);	//指定のObjアドレスを渡す
	}

	//見つからなかった場合
	return nullptr;	//nullを返す
}

//指定したタグの2Dオブジェクトのリストを取得
std::vector<Object2D* >ObjectManager::GetObject2DListByTag(Object2D::Tag tag) {
	std::vector<Object2D* >ret;	//指定Objを収納するコンテナ
	
	for (auto itr = mObject2DList.begin();
		itr != mObject2DList.end();
		itr++) {
		//指定Objが見つかった場合
		if ((*itr)->GetTag() == tag) {
			ret.push_back((*itr));	//この関数で返すコンテナへ収納
		}
	}

	return ret;
}


//	--3D--	//
//3Dオブジェクトの追加
void ObjectManager::AddObject(Object3D* object3D){
	mObject3DList.push_back(object3D);
}

//2Dオブジェクトの全削除
void ObjectManager::DeleteAll3D() {
	for (auto itr = mObject3DList.begin();
		itr != mObject3DList.end();) {
		Object3D* temp = *itr;	//3DObjのポインタをローカル一時避難
		itr = mObject3DList.erase(itr);	//リストから削除

		delete temp;	//ローカルデータを解放
		temp = nullptr;	//一応null
	}
}

//削除する必要のあるオブジェクトがあれば削除する
void ObjectManager::DeleteAll3DIfNeeded() {
	for (auto itr = mObject3DList.begin();
		itr != mObject3DList.end();) {

		//削除フラグが立っている場合
		if ((*itr)->IsDeleteFlag()) {
			Object3D* temp = *itr;	//3DObjのポインタをローカルへ一時避難
			itr = mObject3DList.erase(itr);	//リストから消去

			delete temp;	//ローカルデータを解放
			temp = nullptr;	//一応null
		}

		//削除フラグが立っていない場合
		else {
			itr++;	//そのまま通過。要素を進める
		}
	}
}

//指定したタグの2Dオブジェクトを取得
Object3D* ObjectManager::GetObject3DByTag(Object3D::Tag3D tag) {
	auto itr = std::find_if(
		mObject3DList.begin(),
		mObject3DList.end(),
		[&](Object3D* obj) {return obj->GetTag() == tag; }
	);

	//指定objが見つかった場合
	if (itr != mObject3DList.end()) {
		return (*itr);	//指定objのアドレスを返す
	}

	//指定objが見つからなかった場合
	return nullptr;	//nullを返す
}

//指定したタグの2Dオブジェクトのリストを取得
std::vector<Object3D* >ObjectManager::GetObject3DListByTag(Object3D::Tag3D tag) {
	std::vector<Object3D* >ret;	//指定Objを収納するコンテナ

	for (auto itr = mObject3DList.begin();
		itr != mObject3DList.end();
		itr++) {
		//指定Objが見つかった場合
		if ((*itr)->GetTag() == tag) {
			ret.push_back((*itr));	//この関数で返すコンテナへ収納
		}
	}

	return ret;
}