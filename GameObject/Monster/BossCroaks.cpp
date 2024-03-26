#include "pch.h"
#include "BossCroaks.h"
#include "SceneGame.h"
#include "Bullet/BulletCroaksFirefly.h"

BossCroaks::BossCroaks(const std::string& name)
	:ObjectMonster(name)
{
}

void BossCroaks::Init()
{
	ObjectMonster::Init();

	hasHitBox = true;
}

void BossCroaks::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	animator.SetTarget(&sprite);
	SetPosition({300,0});
	Intro();
}

void BossCroaks::Update(float dt)
{
	ObjectMonster::Update(dt);
	if (hp == 0 && state < State::None)
	{
		Death();
	}

	switch (state)
	{
	case BossCroaks::State::Idle:
		if (PatternTimer(dt))
		{
			if (hp > maxHp * 0.60)
			{
				SetState(State::Pattern1);
			}
			else if (hp <= maxHp * 0.60)
			{
				SetState(State::Pattern2);
			}
		}
		break;
	case BossCroaks::State::Pattern1:
		if (shootCount >= 3)
		{
			shootCount = 0;
			SetState(State::Idle);
		}
		else
		{
			SetState(State::Shoot);
		}
		break;
	case BossCroaks::State::Pattern2:
		if (FanTimer(dt))
		{
			SetState(State::Idle);
		}
		else
		{
			SetState(State::Fan);
		}
		break;
	case BossCroaks::State::Fan:
		if (state == State::Fan)
		{
			if (FanTimer(dt))
			{
				fanTimer = 0;
				animator.Play("animations/CroaksFanOutro.csv");
				animator.AddEvent("animations/CroaksFanOutro.csv", animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCroaks::Idle, this));
			}
		}
		break;
	}

	auto bounds = sprite.getGlobalBounds();
	float shrinkFactor = 0.6f;
	float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
	float heightReduction = bounds.height * (1 - shrinkFactor) / 2;
	customBounds = sf::FloatRect(bounds.left + widthReduction, bounds.top, bounds.width * shrinkFactor, bounds.height);
}

void BossCroaks::LateUpdate(float dt)
{
	ObjectMonster::LateUpdate(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SetState(State::Pattern2);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetState(State::Pattern1);
	}

}

void BossCroaks::Intro()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/CroaksIntro.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCroaks::Idle, this));
}

void BossCroaks::Idle()
{
	SetState(State::Idle);
}

void BossCroaks::Fan()
{
}

void BossCroaks::FanEnd()
{
	SetState(State::Idle);
}

void BossCroaks::Shoot()
{
	if (shootCount < 3)
	{
		shootCount++;
		BulletCroaksFirefly::Create(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width * 0.1f, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 0.4f), { -1.f , 0.f }, scene);
	}
	else
	{
		ShootEnd();
	}
}

void BossCroaks::ShootEnd()
{
	shootCount = 0;
	SetState(State::Idle);
}

void BossCroaks::Death()
{
	isAlive = false;
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/CroaksDeath.csv");

}

void BossCroaks::OnDie()
{
	scene->RemoveGo(this);
}

bool BossCroaks::ShootTimer(float dt)
{
	return false;
}

bool BossCroaks::PatternTimer(float dt)
{
	patternTimer += dt;
	if (patternTimer >= patternInterval)
	{
		patternTimer = 0.f;
		return true;
	}
	return false;
}

bool BossCroaks::FanTimer(float dt)
{
	fanTimer += dt;
	if (fanTimer >= fanInterval)
	{
		fanTimer = 0.f;
		return true;
	}
	return false;
}

void BossCroaks::SetState(State state)
{
	this->state = state;
	switch (state)
	{
	case BossCroaks::State::Idle:
		animator.Play("animations/CroaksIdle.csv");
		preState = State::Idle;
		break;
	case BossCroaks::State::Pattern1:
		if (preState == State::Shoot)
		{
			animator.Play("animations/CroaksIdle.csv");
		}
		preState = State::Pattern1;
		break;
	case BossCroaks::State::Pattern2:
		preState = State::Pattern2;
		if (preState == State::Fan)
		{
			animator.Play("animations/CroaksIdle.csv");
		}
		preState = State::Pattern2;
		break;
	case BossCroaks::State::Shoot:
		animator.ClearEvent();
		animator.Play("animations/CroaksShoot.csv");
		if (shootCount >= 2)
		{
			animator.AddEvent("animations/CroaksShoot.csv", 28, std::bind(&BossCroaks::ShootEnd, this));     //3번 shoot하고 마지막 프레임에 idle로 이동
		}
		else
		{
			animator.AddEvent("animations/CroaksShoot.csv", 17, std::bind(&BossCroaks::Shoot, this));
		}
		preState = State::Shoot;
		break;
	case BossCroaks::State::Fan:
		animator.ClearEvent();
		animator.Play("animations/CroaksFanIntro.csv");
		animator.PlayQueue("animations/CroaksFanLoop.csv");
		animator.AddEvent("animations/CroaksFanLoop.csv", 2, std::bind(&BossCroaks::Fan, this));
		preState = State::Fan;
		break;
	case BossCroaks::State::None:
		break;
	default:
		break;
	}
}

sf::FloatRect BossCroaks::GetCustomBounds() const
{
	return customBounds;
}
