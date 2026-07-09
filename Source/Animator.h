#pragma once
#include "Component.h"
#include <string>
#include <unordered_map>

class ModelRenderer;

class Animator : public Component
{
private:
	struct AnimationClip {
		int mnAnimationHandle = -1;

		bool mbLoop = true;
		float mfDefaultSpeed = 1.0f;
	};

	struct AnimationInstance {
		AnimationClip* mpClip;

		int mnAttachIndex = -1;
		float mfTime = 0.0f;
	};
public:
	void Init() override;
	void Update() override;
	void UpdateBlend();
	void UpdateCurrentAnimation();
	void UpdateOldAnimation();
	void UpdateAnimationInstance(AnimationInstance& _instance, float _blendRate);;

	void Play(const std::string& _animationName, bool _forcePlay = false);
	void CrossFade(const std::string& _animationName, float _fadeTime, bool _isForce = false);
	void PrepareAnimationChange(const std::string& _animationName, AnimationClip* _clip);
	void AttachCurrentAnimation();
	void BeginBlend(float _blendTime);

	void AddAnimation(const std::string& _animtionIndexName, const std::string& _animationFilename);

	bool IsFinished() const { return mbIsFinished; }
	void SetSpeed(float _speed) { mfPlaySpeed = _speed; }
	float GetSpeed() { return mfPlaySpeed; }

private:
	ModelRenderer* mpModelRenderer = nullptr;

	std::unordered_map<std::string, AnimationClip> mAnimationTable;

	AnimationInstance mCurrentAnimation;
	AnimationInstance mOldAnimation;

	std::string msCurrentAnimationName;

	float mfPlaySpeed = 1.0f;
	bool mbIsFinished = false;

	float mfBlendRate = 1.0f;
	float mfBlendDuration = 0.0f;
	float mfBlendElapsed = 0.0f;
};