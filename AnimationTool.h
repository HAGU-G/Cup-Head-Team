#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class AnimationTool : public SpriteGo
{
protected:
	Animator animator;
	std::string exampleAni;

public:
	AnimationTool(const std::string& name = "");
	~AnimationTool() override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	void SetAnimationClipId(const std::string& id);
};

