#include "pch.h"
#include "BossCarnation.h"
#include "Effect/EffectCarnationCreating.h"
#include "Effect//EffectCarnationFireSeed.h"
#include "Bullet/BulletCarnationBoomerang.h"
#include "Bullet/BulletCarnationAcon.h"
#include "Bullet/BulletCarnationFireSeed.h"
#include "SceneGame.h"

BossCarnation::BossCarnation(const std::string& name)
	:ObjectMonster(name)
{
}

void BossCarnation::Init()
{
	ObjectMonster::Init();

	viewSize = FRAMEWORK.GetStageViewSize();
	defaultPos = { viewSize.x * 0.5f * 0.663f, 100.f };
}

void BossCarnation::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));
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
		if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
		{
			Creating();
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
		{
			FireSeed();
		}
	}
	else if (state == State::FinalIdle)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Num5))
		{
			FinalFiringPollen();
		}
	}

	switch (state)
	{
	case BossCarnation::State::Idle:
		SetPosition(defaultPos);
		break;
	case BossCarnation::State::FinalIdle:
		SetPosition(defaultPos);
		break;
	default:
		break;
	}

	auto bounds = sprite.getGlobalBounds();
	float shrinkFactor = 0.1f;
	float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
	float heightReduction = bounds.height * (1 - shrinkFactor) / 2;
	customBounds = sf::FloatRect(bounds.left + widthReduction, bounds.top, bounds.width * shrinkFactor, bounds.height);

	GameObject* player = scene->FindGo("Player");
	setDirection = sf::Vector2f({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.3f, sprite.getPosition().y - sprite.getGlobalBounds().height * 0.5f });
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
	sf::Vector2f Pos = GetPosition();
	SetPosition({ Pos.x + 160.f,Pos.y });
	animator.Play("animations/carnationBossFa_High.csv");

	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));
}

void BossCarnation::FaLow()
{
	SetState(State::None);
	animator.ClearEvent();
	sf::Vector2f Pos = GetPosition();
	SetPosition({ Pos.x + 160.f,Pos.y + 20.f });
	animator.Play("animations/carnationBossFa_Low.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));
}

void BossCarnation::Creating()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/carnationBossCreating.csv");
	animator.AddEvent("animations/carnationBossCreating.csv", 20, std::bind(&BossCarnation::CreatingEffect, this));
	animator.AddEvent("animations/carnationBossCreating.csv", 54, std::bind(&BossCarnation::CreatingEffect, this));
	animator.AddEvent("animations/carnationBossCreating.csv", 86, std::bind(&BossCarnation::CreatingEffect, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));
}

void BossCarnation::CreatingEffect()
{
	EffectCarnationCreating::Create({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.3f,sprite.getPosition().y - sprite.getGlobalBounds().height*0.5f}, {1.f, 0.f}, scene);

	if (Utils::RandomRange(0, 100) < 50)
	{
		BulletCarnationAcon::Create({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.3f,sprite.getPosition().y - sprite.getGlobalBounds().height * 0.5f - 100.f }, { -1.f,0.f }, scene, 1.f);
		BulletCarnationAcon::Create({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.3f,sprite.getPosition().y - sprite.getGlobalBounds().height * 0.5f }, { -1.f,0.f }, scene, 1.5f);
		BulletCarnationAcon::Create({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.3f,sprite.getPosition().y - sprite.getGlobalBounds().height * 0.5f + 100.f }, { -1.f,0.f }, scene, 2.f);
	}
	else
	{
		BulletCarnationBoomerang::Create({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.3f,sprite.getPosition().y - sprite.getGlobalBounds().height * 0.5f }, { -1.f,0.f }, scene);
	}
}

void BossCarnation::FireSeedEffect()
{
	EffectCarnationFireSeed::Create({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.1f -10.f,sprite.getPosition().y - sprite.getGlobalBounds().height * 0.9f }, { 1.f,0.f }, scene);
}

void BossCarnation::FireSeed()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/carntionBossFireSeed.csv");
	animator.AddEvent("animations/carntionBossFireSeed.csv", 6, std::bind(&BossCarnation::FireSeedEffect, this));
	animator.AddEvent("animations/carntionBossFireSeed.csv", 16, std::bind(&BossCarnation::FireSeedEffect, this));
	animator.AddEvent("animations/carntionBossFireSeed.csv", 26, std::bind(&BossCarnation::FireSeedEffect, this));
	animator.AddEvent("animations/carntionBossFireSeed.csv", 36, std::bind(&BossCarnation::FireSeedEffect, this));
	animator.AddEvent("animations/carntionBossFireSeed.csv", 46, std::bind(&BossCarnation::FireSeedEffect, this));
	animator.AddEvent("animations/carntionBossFireSeed.csv", 56, std::bind(&BossCarnation::FireSeedEffect, this));
	animator.AddEvent("animations/carntionBossFireSeed.csv", 66, std::bind(&BossCarnation::FireSeedEffect, this));

	animator.AddEvent("animations/carntionBossFireSeed.csv", 26, std::bind(&BossCarnation::AddSeed, this));
	animator.AddEvent("animations/carntionBossFireSeed.csv", 36, std::bind(&BossCarnation::AddSeed, this));
	animator.AddEvent("animations/carntionBossFireSeed.csv", 46, std::bind(&BossCarnation::AddSeed, this));
	animator.AddEvent("animations/carntionBossFireSeed.csv", 56, std::bind(&BossCarnation::AddSeed, this));
	animator.AddEvent("animations/carntionBossFireSeed.csv", 66, std::bind(&BossCarnation::AddSeed, this));

	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));
}

void BossCarnation::AddSeed()
{
	int rnadom = Utils::RandomRange(0, 101);
	if (rnadom <= 33)
	{
		BulletCarnationFireSeed::Create({ position.x - Utils::RandomRange(0.f,800.f)-200, position.y - 800 }, { 0.f , 1.f }, scene, 1);
	}
	else if (rnadom <= 66)
	{
		BulletCarnationFireSeed::Create({ position.x - Utils::RandomRange(0.f, 800.f) - 200, position.y - 800 }, { 0.f , 1.f }, scene, 0);
	}
	else if(rnadom <= 100)
	{
		BulletCarnationFireSeed::Create({ position.x - Utils::RandomRange(0.f, 800.f) - 200, position.y - 800 }, { 0.f , 1.f }, scene, 2);
	}
}

void BossCarnation::Intro()
{
	SetState(State::None);
	animator.ClearEvent();
	sf::Vector2f Pos = GetPosition();
	SetPosition({ Pos.x + 155.f,Pos.y });
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

void BossCarnation::FinalFiringPollen()
{
	SetState(State::None);
	animator.ClearEvent();
	sf::Vector2f Pos = GetPosition();
	SetPosition({ Pos.x - 50.f,Pos.y });
	animator.Play("animations/carnationFiringPollen.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::FinalIdle, this));
}

void BossCarnation::Death()
{
	isAlive = false;
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
		animator.Play("animations/carnationFinalIdle.csv");
		preState = State::FinalIdle;
		break;
	default:
		break;
	}
}

sf::FloatRect BossCarnation::GetCustomBounds() const
{
	return customBounds;
}

//
//void BossCarnation::Draw(sf::RenderTexture& window)
//{
//	ObjectMonster::Draw(window);
//	
//}
