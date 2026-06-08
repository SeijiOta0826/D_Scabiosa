#include"Object2D.h"
#include"Texture.h"
#include "Scene.h"


Object2D::Object2D(std::string filename, VECTOR initPos)
	:mvPosition(initPos)
	, mbDeleteFlag(false) {
	//現在シーンのObjectManagerに自身(this)を追加する
	//Master::mpSceneManager->GetCurrentScene()->GetObjectManager()->AddObject(this);

	mpTexture = new Texture(filename, initPos, true);	//画像生成

	mfsizeX = mpTexture->GetSizeX();	//テクスチャのサイズをobjとして取得(X)
	mfsizeY = mpTexture->GetSizeY();	//テクスチャのサイズをobjとして取得(Y)
	mnHandle = mpTexture->GetHandle();	//テクスチャのハンドルを取得

	SetZOrder(0.0f);	//レイヤーの初期化
}

Object2D::~Object2D() {
	if (mpTexture != nullptr) {
		delete mpTexture;
	}
}

//更新処理
void Object2D::Update() {
	mpTexture->SetPosition(mvPosition);	//テクスチャーの描画座標を更新
	mpTexture->Update();	//テクスチャーの更新処理
}

//描画処理
void Object2D::Draw(){
	mpTexture->Draw();	//テクスチャの描画処理
}

