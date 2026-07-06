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

	void Play(const std::string& _animationName, bool _forcePlay = false);
	void CrossFade(const std::string& _animationName, float _fadeTime, bool _isForce = false);
	void SetCurrentAnimation(const std::string& _animationName, AnimationClip* _clip);
	void AttachAniamtion();
	void BeginBlend(float _blendTime);

	void AddAnimation(const std::string& _animtionIndexName, const std::string& _animationFilename);

private:
	ModelRenderer* mpModelRenderer = nullptr;

	std::unordered_map<std::string, AnimationClip> mAnimationTable;

	AnimationInstance mCurrentAnimation;
	AnimationInstance mOldAnimation;

	std::string msCurrentAnimationName;

	float mfBlendRate = 1.0f;
	float mfBlendSpeed = 0.1f;
	float mfBlendDuration = 0.0f;
	float mfBlendElapsed = 0.0f;
};