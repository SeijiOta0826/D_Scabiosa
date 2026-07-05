#include "Animator.h"

#include "DxLib.h"
#include "GameObject.h"
#include "ModelRenderer.h"

void Animator::Init() {
	mpModelRenderer = mpGameObject->GetComponent<ModelRenderer>();
}

void Animator::Update() {
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

void Animator::Play(const std::string& _animationName, bool _forcePlay) {
	//-- モデルハンドルの取得 --//
	if (!mpModelRenderer) return;
	int nModelHandle = mpModelRenderer->GetModelHandle();

	//-- 指定アニメーションが存在するかチェック --//
	auto it = mAnimationTable.find(_animationName);
	if (it == mAnimationTable.end()) return;

	//-- 同じアニメーションを指定していないかチェック --//
	if (!_forcePlay &&
		msCurrentAnimationName == _animationName) {
		return;
	}

	mOldAnimation = mCurrentAnimation;

	//-- 新しいアニメーションを設定 --//
	msCurrentAnimationName = _animationName;
	mCurrentAnimation.mpClip = &it->second;
	mCurrentAnimation.mfTime = 0.0f;

	mCurrentAnimation.mnAttachIndex =
		MV1AttachAnim(
			nModelHandle,
			0,
			mCurrentAnimation.mpClip->mnAnimationHandle,
			TRUE
		);

	//-- ブレンド開始 --//
	mfBlendRate =
		(mOldAnimation.mnAttachIndex == -1)
		? 1.0f
		: 0.0f;
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
	AttachAniamtion();

	//Todo : ブレンドの初期処理をする
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

void Animator::AttachAniamtion() {
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