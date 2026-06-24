#include "Model.h"
#include "AttachmentModel.h"

#include "ResourceManager.h"

Model::Model(const std::string& filename,const Vector3& initPos)
	:mvPosition(initPos)
	, mpAttachment(nullptr)
	, mvScale(Vector3(1.0f, 1.0f, 1.0f))
	, mnChangeTextureHandle(-1)
	, mnRootFrameIndex(-1)
	, mmInitializeMatrix(MGetIdent()) {
	mnHandle = ResourceManager::GetInstance().LoadModel(filename.c_str());	//モデル読み込み

	mpSeparateAnimation = std::make_unique<SeparateModelAnimation>(mnHandle);	// 分割アニメーションクラスの生成

	MV1SetScale(mnHandle, mvScale.ToDxVector());	//拡大値の初期化
}

// アニメーション追加
void Model::AddAnimation(AnimationState state, std::string filename) {
	if (mpSeparateAnimation != nullptr) {
		mpSeparateAnimation->AddAnimation(state, filename);
	}
}


//-- アニメーションによる移動を防ぐ関係 --//
// 初期行列の設定
void Model::SetupInitializeMatrix(std::string rootFrameName) {
	mnRootFrameIndex = MV1SearchFrame(mnHandle, rootFrameName.c_str());	// 指定されたフレーム名が存在するか探す

	// フレームが有効なインデックスだった場合
	if (ValidRootFrameIndex()) {
		mmInitializeMatrix = MV1GetFrameBaseLocalMatrix(mnHandle, mnRootFrameIndex);	//ルートボーンの初期姿勢を保存
	}
}

// 有効なフレームかどうかの判定
bool Model::ValidRootFrameIndex() {
	return (mnRootFrameIndex != -1 && mnRootFrameIndex != -2);	// MV1SearchFrame では -1 か -2 がエラーで帰ってくるので、その判定用
}


Model::~Model() {
	if (mpAttachment != nullptr) mpAttachment->SetDeleteFlag(true);			// アタッチモデルクラスの破棄
	if (mnChangeTextureHandle != -1) DeleteGraph(mnChangeTextureHandle);	// テクスチャを切り替えている場合はそのテクスチャの破棄
	
	MV1DeleteModel(mnHandle);	//読み込んだモデルの削除
}

//更新処理
void Model::Update(float _deltaTime) {

	//-- 固定した行列を一旦解除する --//
	 
	//ルートフレームが見つかっている場合
	if (ValidRootFrameIndex()) {
		MV1ResetFrameUserLocalMatrix(mnHandle, mnRootFrameIndex);	//固定した行列のリセット
	}

	//-- 主要な更新処理 --//
	if (mpSeparateAnimation != nullptr) mpSeparateAnimation->Update(_deltaTime);	//分割アニメーションデータの更新

	//-- アニメーションによるモデル移動を無効化する --//
	{
		// アニメーションで移動している成分だけを初期値に戻すことで、アニメーションでの移動を無効化しているようにみせる。
		// note: 実験的な実装なので、上手く行かないアニメーションもあるかも。
		if (ValidRootFrameIndex()) {
			MATRIX Matrix = MV1GetFrameLocalMatrix(mnHandle, mnRootFrameIndex);	//アニメーション + ボーン操作 + IKを含めた現瞬間の姿勢の行列取得
			Matrix.m[3][0] = mmInitializeMatrix.m[3][0];	// X座標を初期値に戻す
			//result.m[3][1] = mmInitializeMatrix.m[3][1];	// Y成分だけは一旦反映しないようにしておく（反映してもよいが、見た目が少しおかしくなることが多い）
			Matrix.m[3][2] = mmInitializeMatrix.m[3][2];	// Z座標を初期値に戻す
			MV1SetFrameUserLocalMatrix(mnHandle, mnRootFrameIndex, Matrix);	//補正した行列を設定
		}
	}

	MV1SetPosition(mnHandle, mvPosition.ToDxVector());		//座標設定
	MV1SetRotationXYZ(mnHandle, mvRotation.ToDxVector());	//回転設定
}

//描画処理
void Model::Draw() {
	MV1DrawModel(mnHandle);	//モデルの描画
}

// アニメ－ション切り替え
void Model::ChangeAnimation(AnimationState state, bool isForce) {
	if (mpSeparateAnimation != nullptr) mpSeparateAnimation->ChangeAnimation(state, 0, isForce);	//分割アニメーション切り替え
}

//ループ設定
void Model::SetLoop(bool loop) {
	if (mpSeparateAnimation != nullptr) mpSeparateAnimation->SetLoop(loop);		//分割アニメーションのループ設定
}

//ループ後に再生するアニメーションの設定
void Model::SetLoopFinishState(AnimationState state) {
	if (mpSeparateAnimation != nullptr) mpSeparateAnimation->SetLoopFinishState(state);	//ループ後に再生するアニメーションの設定(分割)
}

//モーションのブレンド設定
void Model::SetAnimationBlend(bool isBlend) {
	if (mpSeparateAnimation != nullptr) mpSeparateAnimation->SetAnimationBlend(isBlend);	//モーションのブレンド設定(分割)
}

//現在のアニメーション状態を取得
AnimationState Model::GetNowState() {
	AnimationState ret = AnimationState::ANIMATION_MAX;	// 無効値で初期化

	if (mpSeparateAnimation != nullptr) ret = mpSeparateAnimation->GetNowState();	//分割アニメーションの状態取得

	return ret;
}

bool Model::IsAnimationLoopFinish() {
	bool ret = false;	//未終了で初期化

	if (mpSeparateAnimation != nullptr) ret = mpSeparateAnimation->IsLoopFinish();	//分割アニメーションのループ終了状態を取得

	return ret;
}


//-- アタッチメント関係 --//
//アタッチメントを追加
void Model::AddAttachment(std::string filename, std::string attachFrameName){
	int frameIndex = MV1SearchFrame(mnHandle, attachFrameName.c_str());	//アタッチ先のフレーム番号を取得
	mpAttachment = std::make_unique<AttachmentModel>(filename, mnHandle, frameIndex);	//アタッチメントモデルの生成
}

//アタッチモデルの座標取得
Vector3 Model::GetAttachmentPosition() {

	if (mpAttachment != nullptr) {
		Vector3 vec = Vector3(0.0f, -50.0f, 0.0f);	//(剣とか武器専用)良い感じに持ってるぐらいの位置に調整
		MATRIX matrix = MV1GetFrameLocalWorldMatrix(mpAttachment->GetHandle(), 0);	//行列の取得
		vec = Vector3(VTransform(vec.ToDxVector(), matrix));	//行列情報をもとに座標変換する
		return vec;	
	}

	return VGet(0.0f, 0.0f, 0.0f);	//アタッチメントがない場合は原点にしておく
}

// アニメーション速度補正
void Model::SetAnimationSpeedScale(float speed) {
	//if (mpAnimation != nullptr)
	if (mpSeparateAnimation != nullptr) mpSeparateAnimation->SetAnimationSpeed(speed);	//分割アニメーションの速度補正
}

// アニメーション進捗率取得
float Model::GetAnimationProgressRate() {
	float ret = 0.0f;	//未進行で初期化

	//if (mpAnimation != nullptr)
	if (mpSeparateAnimation != nullptr) ret = mpSeparateAnimation->GetAnimationProgressRate();	//分割アニメーションの進捗率取得

	return ret;
}