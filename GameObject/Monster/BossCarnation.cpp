#include "pch.h"
#include "BossCarnation.h"
#include "Effect/EffectOnionTears.h"

BossCarnation::BossCarnation(const std::string& name)
	:ObjectMonster(name)
{
}

void BossCarnation::Init()
{
	ObjectMonster::Init();

	RES_MGR_TEXTURE.Load("resource/carnationBossIntro.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossIdle.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossFa_High.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossFa_Low.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossFinalIntro.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossFinalIdle.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossDie.png");
}

void BossCarnation::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	animator.SetTarget(&sprite);
	Intro();
}

void BossCarnation::Update(float dt)
{
	ObjectMonster::Update(dt);
	if (hp == 0 && state < State::None)
	{
		Death();
	}
	if (hp <= maxHp * 0.95 && state == State::Idle)
	{
		FinalIntro();
	}
	if (state == State::Idle)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
		{
			FaHigh();
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
		{
			FaLow();
		}
	}

	switch (state)
	{
	case BossCarnation::State::Idle:
		break;
	case BossCarnation::State::FinalIdle:
		break;
	default:
		break;
	}
}

void BossCarnation::LateUpdate(float dt)
{
	ObjectMonster::LateUpdate(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		OnDamage(10);
	}
}

void BossCarnation::FaHigh()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/carnationBossFa_High.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));
}

void BossCarnation::FaLow()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/carnationBossFa_Low.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));
}

void BossCarnation::Intro()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/carnationBossIntro.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));

}

void BossCarnation::Idle()
{
	SetState(State::Idle);
}

void BossCarnation::FinalIntro()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/carnationBossFinalIntro.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::FinalIdle, this));
}

void BossCarnation::FinalIdle()
{
	SetState(State::FinalIdle);
}

void BossCarnation::Death()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/carnationBossDie.csv");
}

void BossCarnation::OnDie()
{
	scene->RemoveGo(this);
}

bool BossCarnation::PatternTimer(float dt)
{
	patternTimer += dt;
	if (patternTimer >= patternInterval)
	{
		patternTimer = 0.f;
		return true;
	}
	return false;
}

void BossCarnation::SetState(State state)
{
	this->state = state;
	switch (state)
	{
	case BossCarnation::State::Idle:
		animator.Play("animations/carnationBossIdle.csv");
		preState = State::Idle;
		break;
	case BossCarnation::State::FinalIdle:
		animator.Play("animations/carnationBossFinalIdle.csv");
		preState = State::FinalIdle;
		break;
	default:
		break;
	}
}

bool BossCarnation::CollisionCheck()
{
	return true;
}
