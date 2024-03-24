#include "pch.h"
#include "BossCarnation.h"
#include "Effect/EffectCarnationCreating.h"
#include "Effect//EffectCarnationFireSeed.h"
#include "Bullet/BulletCarnationBoomerang.h"
#include "Bullet/BulletCarnationAcon.h"
#include "Bullet/BulletCarnationFireSeed.h"

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
	RES_MGR_TEXTURE.Load("resource/carntionBossFireSeed.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossFinalIntro.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossFinalIdle.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossDie.png");

	mainBg = new SpriteGo("mainBg");
	mainBg->SetTexture("resource/Sprite/stage02/flower_bg_main1.png");
	mainBg->SetPosition({ 0.f,140.f });
	mainBg->SetOrigin(Origins::BC);
	mainBg->sortLayer = -1;
	mainBg->SetScale({ 0.8f,0.8f });

	skyBg = new SpriteGo("skyBg");
	skyBg->SetTexture("resource/Sprite/stage02/flower_bg_sky.png");
	skyBg->SetPosition({ 0.f,-190.f });
	skyBg->SetOrigin(Origins::BC);
	skyBg->sortLayer = -2;
	skyBg->SetScale({ 0.8f,0.8f });

	cloudBg = new SpriteGo("cloudBg");
	cloudBg->SetTexture("resource/Sprite/stage02/flower_bg_clouds_b.png");
	cloudBg->SetPosition({ 0.f,-190.f });
	cloudBg->SetOrigin(Origins::BC);
	cloudBg->sortLayer = -2;
	cloudBg->SetScale({ 0.8f,0.8f });

	frontCloudBg = new SpriteGo("frontCloudBg");
	frontCloudBg->SetTexture("resource/Sprite/stage02/flower_bg_clouds_a.png");
	frontCloudBg->SetPosition({ 0.f,-190.f });
	frontCloudBg->SetOrigin(Origins::BC);
	frontCloudBg->sortLayer =-2;
	frontCloudBg->SetScale({ 0.8f,0.8f });

	cloudBg2 = new SpriteGo("cloudBg2");
	cloudBg2->SetTexture("resource/Sprite/stage02/flower_bg_clouds_b.png");
	cloudBg2->SetPosition({ cloudBg->GetGlobalBounds().width,-190.f});
	cloudBg2->SetOrigin(Origins::BC);
	cloudBg2->sortLayer = -2;
	cloudBg2->SetScale({ 0.8f,0.8f });

	frontCloudBg2 = new SpriteGo("frontCloudBg2");
	frontCloudBg2->SetTexture("resource/Sprite/stage02/flower_bg_clouds_a.png");
	frontCloudBg2->SetPosition({ frontCloudBg->GetGlobalBounds().width,-190.f});
	frontCloudBg2->SetOrigin(Origins::BC);
	frontCloudBg2->sortLayer = -2;
	frontCloudBg2->SetScale({ 0.8f,0.8f });

	frontBush = new SpriteGo("frontBush");
	frontBush->SetTexture("resource/Sprite/stage02/flower_bg_fg-bush.png");
	frontBush->SetPosition({ 310.f,80.f });
	frontBush->SetOrigin(Origins::BL);
	frontBush->sortLayer = 1;
	frontBush->SetScale({ 0.8f,0.8f });

	frontBg = new SpriteGo("frontBg");
	frontBg->SetTexture("resource/Sprite/stage02/flower_bg_fg.png");
	frontBg->SetPosition({ 0.f,150.f });
	frontBg->SetOrigin(Origins::BC);
	frontBg->sortLayer = 2;
	frontBg->SetScale({ 0.8f,0.8f });

	defaultPos = GetPosition();
}

void BossCarnation::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	animator.SetTarget(&sprite);
	SCENE_MGR.GetCurrentScene()->AddGo(mainBg);
	SCENE_MGR.GetCurrentScene()->AddGo(skyBg);
	SCENE_MGR.GetCurrentScene()->AddGo(cloudBg);
	SCENE_MGR.GetCurrentScene()->AddGo(frontCloudBg);
	SCENE_MGR.GetCurrentScene()->AddGo(cloudBg2);
	SCENE_MGR.GetCurrentScene()->AddGo(frontCloudBg2);
	SCENE_MGR.GetCurrentScene()->AddGo(frontBush);
	SCENE_MGR.GetCurrentScene()->AddGo(frontBg);
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

	sf::Vector2f cloudPos = cloudBg->GetPosition();
	sf::Vector2f cloudPos2 = cloudBg2->GetPosition();

	sf::Vector2f frontCloudPos = frontCloudBg->GetPosition();
	sf::Vector2f frontCloudPos2 = frontCloudBg2->GetPosition();

	cloudPos.x += cloudSpeed * dt;
	cloudPos2.x += cloudSpeed * dt;

	frontCloudPos.x += frontCloudSpeed * dt;
	frontCloudPos2.x += frontCloudSpeed * dt;

	if (cloudPos.x + cloudBg->GetGlobalBounds().width < 0)
	{
		cloudPos.x = cloudPos2.x + cloudBg->GetGlobalBounds().width;
	}
	else if (cloudPos2.x + cloudBg->GetGlobalBounds().width < 0)
	{
		cloudPos2.x = cloudPos.x + cloudBg->GetGlobalBounds().width;
	}

	if (frontCloudPos.x + frontCloudBg->GetGlobalBounds().width < 0)
	{
		frontCloudPos.x = frontCloudPos2.x + frontCloudBg->GetGlobalBounds().width;
	}
	else if (frontCloudPos2.x + frontCloudBg->GetGlobalBounds().width < 0)
	{
		frontCloudPos2.x = frontCloudPos.x + frontCloudBg->GetGlobalBounds().width;
	}

	cloudBg->SetPosition(cloudPos);
	cloudBg2->SetPosition(cloudPos2);

	frontCloudBg->SetPosition(frontCloudPos);
	frontCloudBg2->SetPosition(frontCloudPos2);

	auto bounds = sprite.getGlobalBounds();
	float shrinkFactor = 0.1f;
	float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
	float heightReduction = bounds.height * (1 - shrinkFactor) / 2;
	customBounds = sf::FloatRect(bounds.left + widthReduction, bounds.top, bounds.width * shrinkFactor, bounds.height);
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
		BulletCarnationAcon::Create({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.3f,sprite.getPosition().y - sprite.getGlobalBounds().height * 0.5f - 100.f }, { -1.f,0.f }, scene);
		BulletCarnationAcon::Create({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.3f,sprite.getPosition().y - sprite.getGlobalBounds().height * 0.5f }, { -1.f,0.f }, scene);
		BulletCarnationAcon::Create({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.3f,sprite.getPosition().y - sprite.getGlobalBounds().height * 0.5f + 100.f }, { -1.f,0.f }, scene);
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
	if (Utils::RandomRange(0, 100) <= 33)
	{
		BulletCarnationFireSeed::Create({ position.x - Utils::RandomRange(0.f,800.f)-200, position.y - 800 }, { 0.f , 1.f }, scene, 1);
	}
	else if (Utils::RandomRange(0, 100) <= 66)
	{
		BulletCarnationFireSeed::Create({ position.x - Utils::RandomRange(0.f, 800.f) - 200, position.y - 800 }, { 0.f , 1.f }, scene, 2);
	}
	else if(Utils::RandomRange(0,100) <= 100)
	{
		BulletCarnationFireSeed::Create({ position.x - Utils::RandomRange(0.f, 800.f) - 200, position.y - 800 }, { 0.f , 1.f }, scene, 0);
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


void BossCarnation::Draw(sf::RenderTexture& window)
{
	ObjectMonster::Draw(window);
	
}
