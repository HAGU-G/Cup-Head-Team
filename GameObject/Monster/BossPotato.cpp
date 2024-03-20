#include "pch.h"
#include "BossPotato.h"
#include "Bullet/BulletPeashot.h"

BossPotato::BossPotato(const std::string& name)
	:ObjectMonster(name)
{
}

void BossPotato::Init()
{
	ObjectMonster::Init();
	shaderHit.loadFromFile("resource/Shader/Hit.frag", sf::Shader::Fragment);
	renderStates.shader = &shaderHit;
}

void BossPotato::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	SetState(State::Intro);
}

void BossPotato::Update(float dt)
{
	ObjectMonster::Update(dt);
	if (hp == 0 && state < State::Death)
	{
		SetState(State::Death);
	}

	switch (state)
	{
	case BossPotato::State::Intro:
		if (PatternTimer(dt))
		{
			SetState(State::Idle);
		}
		break;
	case BossPotato::State::Idle:
		if (PatternTimer(dt))
		{
			SetState(State::Pattern1);
		}
		break;
	case BossPotato::State::Pattern1:
		if (patternCount >= 3)
		{
			SetState(State::Idle);
		}
		else if (PatternTimer(dt))
		{
			patternCount++;
			SetState(State::Shot);
		}
		break;
	case BossPotato::State::Shot:
		if (shotCount < 4)
		{
			shotTimer += dt;
			if (shotTimer >= shotInterval)
			{
				SetTexture("resource/Sprite/stage01/potato/veggie_potato_shoot_0013.png");
				SetOrigin(Origins::BC);
				shotTimer = 0.f;
				shotCount++;
				BulletPeashot::Create(position, Direction::Left, scene);
			}
		}
		else if (true) //애니메이션이 끝났을 때를 조건으로
		{
			shotInterval -= 0.5f;
			SetState(State::Pattern1);
		}
		break;
	case BossPotato::State::Death:
		if (PatternTimer(dt))
		{
			SetState(State::Leave);
		}
		break;
	case BossPotato::State::Leave:
		if (PatternTimer(dt))
		{
			scene->RemoveGo(this);
			SetState(State::None);
		}
		break;
	default:
		break;
	}
}

void BossPotato::LateUpdate(float dt)
{
	ObjectMonster::LateUpdate(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		OnDamage(10);
	}
}

void BossPotato::Intro()
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
	this->state = state;
	switch (state)
	{
	case BossPotato::State::Intro:
		SetTexture("resource/Sprite/stage01/potato/veggie_potato_intro_0001.png");
		SetOrigin(Origins::BC);
		Intro();
		preState = State::Intro;
		break;
	case BossPotato::State::Idle:
		SetTexture("resource/Sprite/stage01/potato/veggie_potato_idle_0001.png");
		SetOrigin(Origins::BC);
		preState = State::Idle;
		break;
	case BossPotato::State::Pattern1:
		if (preState == State::Shot)
		{
			SetTexture("resource/Sprite/stage01/potato/veggie_potato_idle_0001.png");
			SetOrigin(Origins::BC);
		}
		else
		{
			patternCount = 0;
			shotInterval = 1.5f;
		}
		preState = State::Pattern1;
		break;
	case BossPotato::State::Shot:
		shotCount = 0;
		preState = State::Shot;
		break;
	case BossPotato::State::Death:
		SetTexture("resource/Sprite/stage01/potato/veggie_potato_death_0001.png");
		SetOrigin(Origins::BC);
		preState = State::Death;
		break;
	case BossPotato::State::Leave:
		SetTexture("resource/Sprite/stage01/potato/veggie_potato_leave_0024.png");
		SetOrigin(Origins::BC);
		preState = State::Leave;
		break;
	default:
		break;
	}
}

bool BossPotato::CollisionCheck()
{

	return true;
}
