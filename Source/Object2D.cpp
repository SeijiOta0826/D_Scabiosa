#include"Object2D.h"

#include"Texture.h"

#include "Scene.h"
#include "SceneManager.h"
#include "ObjectManager.h"

Object2D::Object2D(std::string filename, VECTOR initPos)
	:mpTexture(std::make_unique<Texture>(filename, initPos, true))
	, mvPosition(initPos)
	, mbDeleteFlag(false) {

	SceneManager::GetInstance().GetCurrentScene()->GetObjectManager()->AddObject(this);	//現在シーンのObjectManagerに自身(this)を追加する

	mfsizeX = mpTexture->GetSizeX();	//テクスチャのサイズをobjとして取得(X)
	mfsizeY = mpTexture->GetSizeY();	//テクスチャのサイズをobjとして取得(Y)
	mnHandle = mpTexture->GetHandle();	//テクスチャのハンドルを取得

	SetZOrder(0.0f);	//レイヤーの初期化
}

//更新処理
void Object2D::Update() {
	mpTexture->SetPosition(mvPosition);	//テクスチャーの描画座標を更新
	mpTexture->Update();				//テクスチャーの更新処理
}

//描画処理
void Object2D::Draw(){
	mpTexture->Draw();	//テクスチャの描画処理
}

