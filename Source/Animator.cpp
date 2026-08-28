#include "Animator.h"

#include "DxLib.h"
#include "GameObject.h"
#include "ModelRenderer.h"

#include "ResourceManager.h"

void Animator::Initialize() {
	// Init時点でModelRendererが存在している前提
	mpModelRenderer = mpGameObject->GetComponent<ModelRenderer>();
}

void Animator::Finalize() {

}

void Animator::Update() {
	//-- モデルデータ有効チェック --//
	if (!mpModelRenderer) return;

	UpdateBlend();
	 
	UpdateCurrentAnimation();

	if (mOldAnimation.mnAttachIndex != -1) {
		UpdateOldAnimation();
	}
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
	if (mfBlendRate >= 1.0f) {
		MV1DetachAnim(
			mpModelRenderer->GetModelHandle(),
			mOldAnimation.mnAttachIndex
		);

		mOldAnimation = {};
	}
}

void Animator::UpdateCurrentAnimation() {
	UpdateAnimationInstance(
		mCurrentAnimation,
		mfBlendRate
	);
}

void Animator::UpdateOldAnimation() {
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
		fDeltaTime * mfPlaySpeed * _instance.mpClip->mfDefaultSpeed;

	//-- ループ判定 --//
	if (_instance.mfTime > fTotalTime) {
		if (_instance.mpClip->mbLoop) {
			_instance.mfTime = 0.0f;
		}
		else {
			_instance.mfTime = fTotalTime;
		}

		mbIsFinished = true;
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
	CrossFade(_animationName, 0.0f, _forcePlay);
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
	if (!_isForce &&
		msCurrentAnimationName == _animationName) {
		return;
	}

	PrepareAnimationChange(_animationName, &it->second);

	AttachCurrentAnimation();

	BeginBlend(_fadeTime);
}

void Animator::PrepareAnimationChange(
	const std::string& _animationName,
	AnimationClip* _clip
) {
	mOldAnimation = mCurrentAnimation;

	msCurrentAnimationName = _animationName;

	mCurrentAnimation.mpClip = _clip;
	mCurrentAnimation.mfTime = 0.0f;

	mbIsFinished = false;
}

void Animator::AttachCurrentAnimation() {
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
	//-- 同一のアニメーション登録を回避 --//
	if (mAnimationTable.find(_animtionName) == mAnimationTable.end()) 
		return;

	//-- アニメーション読み込み & アニメーション登録 --//
	AnimationClip clip;
	clip.mnAnimationHandle = ResourceManager::GetInstance().LoadModel(_animationFilename);

	mAnimationTable.emplace(
		_animtionName,
		std::move(clip)
	);
}