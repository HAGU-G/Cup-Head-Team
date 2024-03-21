#include "pch.h"
#include "BossOnion.h"

BossOnion::BossOnion(const std::string& name)
	:ObjectMonster(name)
{
}

void BossOnion::Init()
{
	ObjectMonster::Init();

	RES_MGR_TEXTURE.Load("resource/onionDeath.png");
	RES_MGR_TEXTURE.Load("resource/onionIdle.png");
	RES_MGR_TEXTURE.Load("resource/onionIntro.png");
	RES_MGR_TEXTURE.Load("resource/onionLeave.png");
	RES_MGR_TEXTURE.Load("resource/onionCry.png");
	RES_MGR_TEXTURE.Load("resource/onionCrying.png");
}

void BossOnion::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	animator.SetTarget(&sprite);
	Intro();
}

void BossOnion::Update(float dt)
{
	ObjectMonster::Update(dt);
	if (hp == 0 && state < State::None)
	{
		Death();
	}
	if (hp <= maxHp * 0.95 && state == State::Idle)
	{
		SetState(State::Pattern1);
	}

	switch (state)
	{
	case BossOnion::State::Idle:
		break;
	case BossOnion::State::Pattern1:
		break;
	case BossOnion::State::Crying:
		break;
	default:
		break;
	}
}

void BossOnion::LateUpdate(float dt)
{
	ObjectMonster::LateUpdate(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		OnDamage(1);
	}
}

void BossOnion::Intro()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/onionIntro.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossOnion::Idle, this));

}

void BossOnion::Idle()
{
	SetState(State::Idle);
}

void BossOnion::Cry()
{
	SetState(State::Crying);
}

void BossOnion::Death()
{
}

void BossOnion::Leave()
{
}

void BossOnion::OnDie()
{
	scene->RemoveGo(this);
}

bool BossOnion::PatternTimer(float dt)
{
	patternTimer += dt;
	if (patternTimer >= patternInterval)
	{
		patternTimer = 0.f;
		return true;
	}
	return false;
}

void BossOnion::SetState(State state)
{
	this->state = state;
	switch (state)
	{
	case BossOnion::State::Idle:
		animator.Play("animations/onionIdle.csv");
		preState = State::Idle;
		break;
	case BossOnion::State::Pattern1:
		if (preState == State::Crying)
		{
			animator.Play("animations/onionCryingReverse.csv");
		}
		animator.PlayQueue("animations/onionCrying.csv");
		animator.AddEvent("animations/onionCrying.csv", 21, std::bind(&BossOnion::Cry, this));
		preState = State::Pattern1;
		break;
	case BossOnion::State::Crying:
		animator.Play("animations/onionCry.csv");
		preState = State::Crying;
		break;
	default:
		break;
	}
}

bool BossOnion::CollisionCheck()
{
	return true;
}
