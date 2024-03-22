#include "pch.h"
#include "BossPotato.h"
#include "SceneDev3.h"
#include "Bullet/BulletPotatoShoot.h"
#include "Bullet/BulletPotatoShootPink.h"

BossPotato::BossPotato(const std::string& name)
	:ObjectMonster(name)
{
}

void BossPotato::Init()
{
	ObjectMonster::Init();
	sprite.setScale(1.3f, 1.3f);

	RES_MGR_TEXTURE.Load("resource/potatoDeath.png");
	RES_MGR_TEXTURE.Load("resource/potatoIdle.png");
	RES_MGR_TEXTURE.Load("resource/potatoIntro.png");
	RES_MGR_TEXTURE.Load("resource/potatoLeave.png");
	RES_MGR_TEXTURE.Load("resource/potatoShoot.png");

	hasHitBox = true;
}

void BossPotato::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	animator.SetTarget(&sprite);
	Intro();

	sceneDev3 = dynamic_cast<SceneDev3*>(SCENE_MGR.GetScene(SceneIds::SceneDev3));
}

void BossPotato::Update(float dt)
{
	ObjectMonster::Update(dt);
	///////////////////////////////////////
	auto bounds = sprite.getGlobalBounds();
	float shrinkFactor = 0.4f;
	float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
	float heightReduction = bounds.height * (1 - shrinkFactor) / 2;
	customBounds = sf::FloatRect(bounds.left + widthReduction, bounds.top, bounds.width * shrinkFactor, bounds.height);
	//////////////////////////////////////
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
	if (++shootCount < 4)
	{
		auto bullet = BulletPotatoShoot::Create(sf::Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 7.f / 8.f), { -1.f, 0.f }, scene);
		dynamic_cast<SceneDev3*>(scene)->AddMonster(bullet);
	}
	else
	{
		auto bullet = BulletPotatoShootPink::Create(sf::Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 7.f / 8.f), { -1.f, 0.f }, scene);
		dynamic_cast<SceneDev3*>(scene)->AddMonster(bullet);
	}
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
	isAlive = false;
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
		shootSpeed += 0.5f;
		shootCount = 0;
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

sf::FloatRect BossPotato::GetCustomBounds() const
{
	return customBounds;
}
