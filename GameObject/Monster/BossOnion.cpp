#include "pch.h"
#include "BossOnion.h"
#include "Effect/EffectOnionTears.h"
#include "Bullet/BulletOnionTear.h"

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
	hasHitBox = true;
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
	if (hp == 0 && state < State::Crying)
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
		if (TearTimer(dt))
		{
			if (rand() % 5 == 0)
			{
				BulletOnionTear::Create(position + sf::Vector2f(tearSide * Utils::RandomRange(sprite.getGlobalBounds().width * 0.6f, FRAMEWORK.GetWindowSize().x * 0.5f),
					-2.f * sprite.getGlobalBounds().height), { 0.f , 1.f }, scene, true);
			}
			else
			{
				BulletOnionTear::Create(position + sf::Vector2f(tearSide * Utils::RandomRange(sprite.getGlobalBounds().width * 0.6f, FRAMEWORK.GetWindowSize().x * 0.5f),
					-2.f * sprite.getGlobalBounds().height), { 0.f , 1.f }, scene);
			}
			tearSide *= -1;
		}
		cryingTimer += dt;
		if (cryingTimer >= cryingDuration)
		{
			cryingTimer = 0.f;
			cryingDuration = 5.f;
			SetState(State::Pattern1);
		}
		break;
	default:
		break;
	}

	auto bounds = sprite.getGlobalBounds();
	float shrinkFactor = 0.1f;
	float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
	float heightReduction = bounds.height * (1 - shrinkFactor) / 2;
	customBounds = sf::FloatRect(bounds.left + widthReduction, bounds.top, bounds.width * shrinkFactor, bounds.height);
}

void BossOnion::LateUpdate(float dt)
{
	ObjectMonster::LateUpdate(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		OnDamage(10);
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

void BossOnion::Tears()
{
	EffectOnionTears::Create(position + sf::Vector2f(sprite.getGlobalBounds().width / 25.f, -sprite.getGlobalBounds().height * 5.f / 8.f), { 1.f, 0.f }, scene, cryingDuration * 1.15f);
	EffectOnionTears::Create(position + sf::Vector2f(-sprite.getGlobalBounds().width * 2.f / 25.f, -sprite.getGlobalBounds().height * 5.f / 8.f), { -1.f, 0.f }, scene, cryingDuration * 1.15f);
}

void BossOnion::Death()
{
	isAlive = false;
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/onionDeath.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossOnion::Leave, this));
}

void BossOnion::Leave()
{
	SetState(State::None);
	animator.Play("animations/onionLeave.csv");
	animator.AddEvent("animations/onionLeave.csv", animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossOnion::OnDie, this));
}

void BossOnion::OnDie()
{
	scene->RemoveGo(this);
}

bool BossOnion::TearTimer(float dt)
{
	tearTimer += dt;
	if (tearTimer >= tearInterval)
	{
		tearTimer = 0.f;
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
			animator.PlayQueue("animations/onionCrying.csv");
		}
		else
		{
			animator.Play("animations/onionCrying.csv");
		}
		animator.ClearEvent();
		animator.AddEvent("animations/onionCrying.csv", 21, std::bind(&BossOnion::Cry, this));
		animator.AddEvent("animations/onionCrying.csv", 11, std::bind(&BossOnion::Tears, this));
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

sf::FloatRect BossOnion::GetCustomBounds() const
{
	return customBounds;
}
