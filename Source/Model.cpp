#include "Model.h"
#include "AttachmentModel.h"

#include "Master.h"

//コンストラクタ
Model::Model(std::string filename, VECTOR initPos, bool isSeparateAnimation)
	:mvPosition(initPos)
	, mpAttachment(nullptr)
	, mvScale(VGet(1.0f, 1.0f, 1.0f))
	, mnChangeTextureHandle(-1)
	, mnRootFrameIndex(-1)              // ★New★
	, mmInitializeMatrix(MGetIdent())   // ★New★
{
	//モデル読み込み
	//mnHandle = MV1LoadModel(filename.c_str());
	mnHandle = Master::mpResource->LoadModel(filename.c_str());

	// ★New★
   // 条件分岐を追加
	if (isSeparateAnimation)
	{
		// 分割アニメーションクラスの生成
		mpSeparateAnimation = new SeparateModelAnimation(mnHandle);
		mpAnimation = nullptr;
	}
	else
	{
		// 通常アニメーションクラスの生成
		mpAnimation = new ModelAnimation(mnHandle);
		mpSeparateAnimation = nullptr;
	}
		
	MV1SetScale(mnHandle, mvScale);	//拡大値の設定
}

// アニメーション追加
void Model::AddAnimation(AnimationState state, std::string filename)
{
	if (mpSeparateAnimation != nullptr)
	{
		mpSeparateAnimation->AddAnimation(state, filename);
	}
}

// ★New★
// 初期行列の設定
void Model::SetupInitializeMatrix(std::string rootFrameName)
{
	// 指定されたフレーム名が存在するか探す
	mnRootFrameIndex = MV1SearchFrame(mnHandle, rootFrameName.c_str());

	// フレームが有効なインデックスだった場合
	if (ValidRootFrameIndex())
	{
		// MV1GetFrameLocalMatrix でも出来るが、
		// 用途的には MV1GetFrameBaseLocalMatrix が合ってそうなので、そっちを使ってみる
		//mmInitializeMatrix = MV1GetFrameLocalMatrix(mnHandle, mnRootFrameIndex);
		mmInitializeMatrix = MV1GetFrameBaseLocalMatrix(mnHandle, mnRootFrameIndex);
	}
}

// ★New★
// 有効なフレームかどうかの判定
bool Model::ValidRootFrameIndex()
{
	// MV1SearchFrame では -1 か -2 がエラーで帰ってくるので、その判定用
	return (mnRootFrameIndex != -1 && mnRootFrameIndex != -2);
}


//デストラクタ
Model::~Model()
{

	//アニメーションクラスの破棄
	if (mpAnimation != nullptr)
	{
		delete mpAnimation;
	}

	// ★New★
   // 分割アニメーションクラスの破棄
	if (mpSeparateAnimation != nullptr)
	{
		delete mpSeparateAnimation;
	}

	// アタッチモデルクラスの破棄
	if (mpAttachment != nullptr)
	{
		mpAttachment->SetDeleteFlag(true);
	}

	// テクスチャを切り替えている場合はそのテクスチャの破棄
	if (mnChangeTextureHandle != -1)
	{
		DeleteGraph(mnChangeTextureHandle);
	}

	//読み込んだモデルの削除
	//note : 読み込んだモデルは勝手に破棄してくれないので、必要なくなったら手動で破棄する
	MV1DeleteModel(mnHandle);
}

//更新
void Model::Update(float _deltaTime)
{

	// ★New★
	// 固定した行列を一旦解除する
	if (ValidRootFrameIndex())
	{
		MV1ResetFrameUserLocalMatrix(mnHandle, mnRootFrameIndex);
	}

	if (mpAnimation != nullptr)
	{
		//アニメーションの更新
		mpAnimation->Update();
	}
	// ★New★
	// 分割アニメーションの更新
	if (mpSeparateAnimation != nullptr)
	{
		mpSeparateAnimation->Update(_deltaTime);
	}

	// ★New★
   // アニメーションで移動している成分だけを初期値に戻すことで、アニメーションでの移動を無効化しているようにみせる。
   // note: 実験的な実装なので、上手く行かないアニメーションもあるかも。
	if (ValidRootFrameIndex())
	{
		auto Matrix = MV1GetFrameLocalMatrix(mnHandle, mnRootFrameIndex);
		MATRIX result = Matrix;
		result.m[3][0] = mmInitializeMatrix.m[3][0];
		//result.m[3][1] = mmInitializeMatrix.m[3][1]; // Y成分だけは一旦反映しないようにしておく（反映してもよいが、見た目が少しおかしくなることが多い）
		result.m[3][2] = mmInitializeMatrix.m[3][2];
		MV1SetFrameUserLocalMatrix(mnHandle, mnRootFrameIndex, result);
	}

	//座標設定
	MV1SetPosition(mnHandle, mvPosition);

	//回転設定
	MV1SetRotationXYZ(mnHandle, mvRotation);
}

//描画
void Model::Draw()
{
	MV1DrawModel(mnHandle);	//モデルの描画
}

// ★New★
// 強制切り替え設定追加(isForce)
// アニメ－ション切り替え
void Model::ChangeAnimation(AnimationState state, bool isForce)
{
	// 
	// 通常 or 分割のどちらかを使っているかで分岐
	if (mpAnimation != nullptr)
	{
		mpAnimation->ChangeAnimation(state);
	}
	if (mpSeparateAnimation != nullptr)
	{
		mpSeparateAnimation->ChangeAnimation(state, 0, isForce);
	}
}

void Model::SetLoop(bool loop)
{
	// ★New★
	// 通常 or 分割のどちらかを使っているかで分岐
	if (mpAnimation != nullptr)
	{
		mpAnimation->SetLoop(loop);
	}
	if (mpSeparateAnimation != nullptr)
	{
		mpSeparateAnimation->SetLoop(loop);
	}
}

void Model::SetLoopFinishState(AnimationState state)
{
	// ★New★
	// 通常 or 分割のどちらかを使っているかで分岐
	if (mpAnimation != nullptr)
	{
		mpAnimation->SetLoopFinishState(state);
	}
	if (mpSeparateAnimation != nullptr)
	{
		mpSeparateAnimation->SetLoopFinishState(state);
	}
}

void Model::SetAnimationBlend(bool isBlend)
{
	// ★New★
	 // 通常 or 分割のどちらかを使っているかで分岐
	if (mpAnimation != nullptr)
	{
		mpAnimation->SetAnimationBlend(isBlend);
	}
	if (mpSeparateAnimation != nullptr)
	{
		mpSeparateAnimation->SetAnimationBlend(isBlend);
	}
}

AnimationState Model::GetNowState()
{
	// ★New★
	// 通常 or 分割のどちらかを使っているかで分岐
	// note: （ほぼありえないが）もしどちらも無ければ、特に設定のない最大値を返すようにする
	AnimationState ret = AnimationState::ANIMATION_MAX;

	if (mpAnimation != nullptr)
	{
		ret = mpAnimation->GetNowState();
	}
	if (mpSeparateAnimation != nullptr)
	{
		ret = mpSeparateAnimation->GetNowState();
	}

	return ret;
}

// ★New★
// 攻撃モーション中かどうか
bool Model::IsAnimationAttack()
{
	// 通常 or 分割のどちらかを使っているかで分岐
	// note: （ほぼありえないが）もしどちらも無ければ、特に設定のない最大値で判定するようにしておく
	AnimationState now = AnimationState::ANIMATION_MAX;

	if (mpAnimation != nullptr)
	{
		now = mpAnimation->GetNowState();
	}
	if (mpSeparateAnimation != nullptr)
	{
		now = mpSeparateAnimation->GetNowState();
	}

	return (now == ANIMATION_ATTACK || now == ANIMATION_ATTACK_2 || now == ANIMATION_ATTACK_3);
}

bool Model::IsAnimationLoopFinish()
{
	// ★New★
	// 通常 or 分割のどちらかを使っているかで分岐
	// note: （ほぼありえないが）もしどちらも無ければ、false を返すようにしておく

	bool ret = false;

	if (mpAnimation != nullptr)
	{
		ret = mpAnimation->IsLoopFinish();
	}
	if (mpSeparateAnimation != nullptr)
	{
		ret = mpSeparateAnimation->IsLoopFinish();
	}

	return ret;
}

//アタッチメントを追加
void Model::AddAttachment(std::string filename, std::string attachFrameName)
{
	//アタッチ先のフレーム番号を取得
	int frameIndex = MV1SearchFrame(mnHandle, attachFrameName.c_str());

	//アタッチメントモデルの生成
	mpAttachment = new AttachmentModel(filename, mnHandle, frameIndex);
}

//アタッチモデルの座標取得
VECTOR Model::GetAttachmentPosition()
{
	//何してるかはいつか理解するべし
	if (mpAttachment != nullptr)
	{
		VECTOR vec = VGet(0.0f, -50.0f, 0.0f);
		//行列の取得
		MATRIX matrix = MV1GetFrameLocalWorldMatrix(mpAttachment->GetHandle(), 0);
		//行列情報をもとに座標変換する
		vec = VTransform(vec, matrix);
		return vec;
	}

	//アタッチメントがない場合は原点にしておく
	return VGet(0.0f, 0.0f, 0.0f);
}

// ★New★
// アニメーション速度補正
void Model::SetAnimationSpeedScale(float speed)
{
	if (mpAnimation != nullptr)
	{

	}
	if (mpSeparateAnimation != nullptr)
	{
		mpSeparateAnimation->SetAnimationSpeed(speed);
	}
}

// ★New★
// アニメーション進捗率取得
float Model::GetAnimationProgressRate()
{
	// 通常 or 分割のどちらかを使っているかで分岐
	// note: （ほぼありえないが）もしどちらも無ければ、0.0f を返すようにしておく

	float ret = 0.0f;

	if (mpAnimation != nullptr)
	{

	}
	if (mpSeparateAnimation != nullptr)
	{
		ret = mpSeparateAnimation->GetAnimationProgressRate();
	}

	return ret;
}