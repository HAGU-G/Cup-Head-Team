#include "pch.h"
#include "BossPotato.h"

BossPotato::BossPotato(const std::string& name)
	:SpriteGo(name)
{
}

void BossPotato::Init()
{
}

void BossPotato::Reset()
{
	SetState(State::Intro);
}

void BossPotato::Update(float dt)
{
	switch (state)
	{
	case BossPotato::State::Intro:
		if (PatternTimer(dt))
		{
			SetState(State::Idle);
		}
		break;
	case BossPotato::State::Idle:
		PatternTimer(dt);
		break;
	case BossPotato::State::Shot:
		break;
	case BossPotato::State::Death:
		break;
	case BossPotato::State::Leave:
		break;
	default:
		break;
	}
}

void BossPotato::LateUpdate(float dt)
{
}

void BossPotato::Intro()
{
}

void BossPotato::Idel()
{
}

void BossPotato::Shot()
{
}

void BossPotato::Death()
{
}

void BossPotato::Leave()
{
}

bool BossPotato::PatternTimer(float dt)
{
	patternTimer += dt;
	if (patternTimer >= patternInterval)
	{
		patternTimer = 0.f;
		return true;
	}
	return false;
}

void BossPotato::SetState(State state)
{
	switch (state)
	{
	case BossPotato::State::Intro:
		SetTexture("resource/Sprite/stage01/potato/veggie_potato_intro_0001.png");
		SetOrigin(Origins::BC);
		break;
	case BossPotato::State::Idle:
		SetTexture("resource/Sprite/stage01/potato/veggie_potato_idle_0001.png");
		SetOrigin(Origins::BC);
		break;
	case BossPotato::State::Shot:
		SetTexture("resource/Sprite/stage01/potato/veggie_potato_shot_0013.png");
		SetOrigin(Origins::BC);
		break;
	case BossPotato::State::Death:
		SetTexture("resource/Sprite/stage01/potato/veggie_potato_death_0001.png");
		SetOrigin(Origins::BC);
		break;
	case BossPotato::State::Leave:
		SetTexture("resource/Sprite/stage01/potato/veggie_potato_leave_0024.png");
		SetOrigin(Origins::BC);
		break;
	default:
		break;
	}
}
