#include "Animator.h"

#include "DxLib.h"
#include "GameObject.h"
#include "ModelRenderer.h"

void Animator::Init() {
	mpModelRenderer = mpGameObject->GetComponent<ModelRenderer>();
}

void Animator::Update() {
	//Todo : //-- ブレンド率の更新処理 --//
	UpdateBlend();
	 
	//Todo : //-- 現在のアニメーションの更新 --//
	UpdateCurrentAnimation();

	//Todo : //-- 前のアニメーションの更新 --//
	UpdateOldAnimation();

	//-- モデルハンドルの取得 --//
	if (!mpModelRenderer) return;
	int nModelHandle = mpModelRenderer->GetModelHandle();

	//-- アニメーションを更新 --//
	MV1SetAttachAnimTime(
		nModelHandle,
		mCurrentAnimation.mnAttachIndex,
		mCurrentAnimation.mfTime
	);

	mCurrentAnimation.mfTime += mCurrentAnimation.mpClip->mfDefaultSpeed;
}

void Animator::UpdateBlend() {
	if (mfBlendRate >= 1.0f) return;	//ブレンド中でない場合

	//-- ブレンド時間更新 --//
	//Todo : fDeltaをDeltaTimeに置き換える
	float fDelta = 1.0f;
	mfBlendElapsed += fDelta;

	//-- ブレンド率計算 --//
	mfBlendRate = mfBlendElapsed / mfBlendDuration;

	if (mfBlendRate > 1.0f) mfBlendRate = 1.0f;

	//-- ブレンド終了 --//
	if (mfBlendRate == 1.0f) {
		MV1DetachAnim(
			mpModelRenderer->GetModelHandle(),
			mOldAnimation.mnAttachIndex
		);

		mOldAnimation = {};
	}
}

void Animator::UpdateCurrentAnimation() {
	//Todo : //-- UpdateAnimationInstance(共通処理関数)の作成 --//
	UpdateAnimationInstance(
		mCurrentAnimation,
		mfBlendRate
	);
}

void Animator::UpdateOldAnimation() {
	//Todo : //-- UpdateAnimationInstance(共通処理関数)の作成 --//
	UpdateAnimationInstance(
		mOldAnimation,
		(1.0f - mfBlendRate)
	);
}

void Animator::UpdateAnimationInstance(
	AnimationInstance& _instance, 
	float _blendRate
) {
	//-- 有効チェック --//
	if (_instance.mpClip == nullptr ||
		_instance.mnAttachIndex == -1) {
		return;
	}

	//-- 総再生時間取得 --//
	float fTotalTime =
		MV1GetAttachAnimTotalTime(
			mpModelRenderer->GetModelHandle(),
			_instance.mnAttachIndex
		);

	//-- 再生時間の更新 --//
	float fDeltaTime = 1.0f;
	_instance.mfTime +=
		fDeltaTime * _instance.mpClip->mfDefaultSpeed;

	//-- ループ判定 --//
	if (_instance.mfTime > fTotalTime) {
		if (_instance.mpClip->mbLoop) {
			_instance.mfTime = 0.0f;
		}
		else {
			_instance.mfTime = fTotalTime;
		}
	}

	MV1SetAttachAnimTime(
		mpModelRenderer->GetModelHandle(),
		_instance.mnAttachIndex,
		_instance.mfTime
	);

	MV1SetAttachAnimBlendRate(
		mpModelRenderer->GetModelHandle(),
		_instance.mnAttachIndex,
		_blendRate
	);
}

void Animator::Play(const std::string& _animationName, bool _forcePlay) {
	CrossFade(_animationName, 0.0f);
}

void Animator::CrossFade(
	const std::string& _animationName,
	float _fadeTime,
	bool _isForce
) {
	//-- モデルハンドルの取得 --//
	if (!mpModelRenderer) return;
	int nModelHandle = mpModelRenderer->GetModelHandle();

	//-- 指定アニメーションが存在するかチェック --//
	auto it = mAnimationTable.find(_animationName);
	if (it == mAnimationTable.end()) return;

	//-- 同じアニメーションを指定していないかチェック --//
	if (_isForce &&
		msCurrentAnimationName == _animationName) {
		return;
	}

	//Todo : CurrentAnimationデータを設定しなおす
	SetCurrentAnimation(_animationName, &it->second);

	//Todo : アニメーションのアタッチ関係を行う
	CurrentAttachAniamtion();

	//Todo : ブレンドの初期処理をする
	BeginBlend(_fadeTime);
}

void Animator::SetCurrentAnimation(
	const std::string& _animationName,
	AnimationClip* _clip
) {
	mOldAnimation = mCurrentAnimation;

	msCurrentAnimationName = _animationName;

	mCurrentAnimation.mpClip = _clip;
	mCurrentAnimation.mfTime = 0.0f;
}

void Animator::CurrentAttachAniamtion() {
	int nModelHandle =
		mpModelRenderer->GetModelHandle();

	mCurrentAnimation.mnAttachIndex =
		MV1AttachAnim(
			nModelHandle,
			0,
			mCurrentAnimation.mpClip->mnAnimationHandle,
			TRUE
		);
}

void Animator::BeginBlend(float _blendTime) {
	mfBlendDuration = _blendTime;

	mfBlendElapsed = 0.0f;

	if (_blendTime <= 0) {
		mfBlendRate = 1.0f;

		if (mOldAnimation.mnAttachIndex != -1) {
			MV1DetachAnim(
				mpModelRenderer->GetModelHandle(),
				mOldAnimation.mnAttachIndex
			);

			mOldAnimation = {};
		}
		return;
	}
	mfBlendRate = 0.0f;
}

void Animator::AddAnimation(
	const std::string& _animtionName,
	const std::string& _animationFilename
) {
	AnimationClip clip;
	//Todo : ResourceManagerを介したアニメーションハンドル取得を行う
	clip.mnAnimationHandle = -1;

	mAnimationTable.emplace(
		_animtionName,
		std::move(clip)
	);
}