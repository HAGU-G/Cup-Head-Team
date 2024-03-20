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

	RES_MGR_TEXTURE.Load("resource/potatoDeath.png");
	RES_MGR_TEXTURE.Load("resource/potatoIdle.png");
	RES_MGR_TEXTURE.Load("resource/potatoIntro.png");
	RES_MGR_TEXTURE.Load("resource/potatoLeave.png");
	RES_MGR_TEXTURE.Load("resource/potatoShoot.png");
}

void BossPotato::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	animator.SetTarget(&sprite);
	Intro();
}

void BossPotato::Update(float dt)
{
	ObjectMonster::Update(dt);
	if (hp == 0 && state < State::None)
	{
		Death();
	}

	switch (state)
	{
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
			SetState(State::Shoot);
		}
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
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/potatoIntro.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossPotato::Idle, this));

}

void BossPotato::Idle()
{
	SetState(State::Idle);
}

void BossPotato::Shoot()
{
	BulletPeashot::Create(position, Direction::Left, scene);
}

void BossPotato::ShootEnd()
{
	SetState(State::Pattern1);
}

void BossPotato::Death()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/potatoDeath.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossPotato::Leave, this));
}

void BossPotato::Leave()
{
	SetState(State::None);
	animator.Play("animations/potatoLeave.csv");
	animator.AddEvent("animations/potatoLeave.csv", animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossPotato::OnDie, this));
}

void BossPotato::OnDie()
{
	scene->RemoveGo(this);
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
	case BossPotato::State::Idle:
		animator.Play("animations/potatoIdle.csv");
		preState = State::Idle;
		break;
	case BossPotato::State::Pattern1:
		if (preState == State::Shoot)
		{
			animator.Play("animations/potatoIdle.csv");
			animator.SetSpeed(1.f);
		}
		else
		{
			patternCount = 0;
			shootSpeed = 1.f;
		}
		preState = State::Pattern1;
		break;
	case BossPotato::State::Shoot:
		animator.SetSpeed(shootSpeed);
		shootSpeed += 1.f;
		animator.ClearEvent();
		animator.Play("animations/potatoShoot.csv");
		animator.PlayQueue("animations/potatoShoot.csv");
		animator.PlayQueue("animations/potatoShoot.csv");
		animator.PlayQueue("animations/potatoShoot.csv");
		animator.AddEvent(animator.GetCurrentCilpId(), 12, std::bind(&BossPotato::Shoot, this));
		animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossPotato::ShootEnd, this));
		preState = State::Shoot;
		break;
	default:
		break;
	}
}

bool BossPotato::CollisionCheck()
{

	return true;
}
