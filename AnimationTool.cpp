#include "pch.h"
#include "AnimationTool.h"

AnimationTool::AnimationTool(const std::string& name)
	:SpriteGo(name)
{
}

AnimationTool::~AnimationTool()
{
}

void AnimationTool::Init()
{
	SpriteGo::Init();
	animator.SetTarget(&sprite);
}

void AnimationTool::Release()
{
	SpriteGo::Release();
}

void AnimationTool::Reset()
{
	SpriteGo::Reset();
	//animator.Play("animations/peashotCreate.csv");
}

void AnimationTool::Update(float dt)
{
	animator.Update(dt);
	SetPosition({ 0.f,0.f });
	SpriteGo::Update(dt);
}

void AnimationTool::SetAnimationClipId(const std::string& id)
{
	exampleAni = id;
	animator.Play("animations/peashotCreate.csv");
}
