#include "pch.h"
#include "BossCarnation.h"
#include "Effect/EffectCarnationCreating.h"
#include "Effect//EffectCarnationFireSeed.h"
#include "Bullet/BulletCarnationBoomerang.h"
#include "Bullet/BulletCarnationAcon.h"
#include "Bullet/BulletCarnationFireSeed.h"
#include "SceneGame.h"
#include "Bullet/BulletCarnationFinalVine.h"
#include "Bullet/BulletCarnationPollen.h"
#include "Bullet/BulletCarnationFinalPlatForm.h"

BossCarnation::BossCarnation(const std::string& name)
	:ObjectMonster(name)
{
	hp = maxHp = 1300;
}

void BossCarnation::Init()
{
	ObjectMonster::Init();

	viewSize = FRAMEWORK.GetStageViewSize();
	defaultPos = { viewSize.x * 0.5f * 0.663f, 100.f };
	hasHitBox = true;
}

void BossCarnation::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	animator.SetTarget(&sprite);

	Intro();
}

void BossCarnation::Update(float dt)
{
	ObjectMonster::Update(dt);
	if (hp == 0)
	{
		BossDieEffect(dt);
		if (state < State::None)
		{
			Death();
		}
	}
	if (hp <= 598 && state == State::Idle)
	{
		FinalIntro();
	}
	if (state == State::Idle)
	{
		patternTimer += dt;
		if (patternTimer >= (float)Utils::RandomRange(5, 10))
		{
			int pattern = Utils::RandomRange(0, 80);
			if (pattern <= 20)
			{
				FaHigh();
				patternTimer = 0;
			}
			else if (pattern <= 40)
			{
				FaLow();
				patternTimer = 0;
			}
			else if (pattern <= 60)
			{
				Creating();
				patternTimer = 0;
			}
			else if (pattern <= 80)
			{

				FireSeed();
				patternTimer = 0;
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
		{
			FireSeed();
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			SetState(State::FinalIdle);
		}
	}
	else if (state == State::FinalIdle)
	{
		finalPollenTimer += dt;
		if(finalPollenTimer >= Utils::RandomRange(4,8))
		{
			FinalFiringPollen();
			finalPollenTimer = 0;
		}
		finalVineTimer += dt;
		if(finalVineTimer >= Utils::RandomRange(4,8))
		{
			FinalAttackPlayForm();
			finalVineTimer = 0;
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


}

void BossCarnation::LateUpdate(float dt)
{
	SetCustomBounds(1.f,0.5f,Origins::TL);
	if (GetState() == State::Idle)
	{
		customBounds.setPosition(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width * 0.2f, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 0.1);
	}
	else if (animator.GetCurrentCilpId() == "animations/carnationBossFa_Low.csv")
	{
		customBounds.setPosition(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width * 0.1f, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 0.6f);
	}
	else if(animator.GetCurrentCilpId() == "animations/carnationBossFa_High.csv")
	{
		customBounds.setPosition(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width * 0.1f, sprite.getGlobalBounds().top);
	}
	else
	{
		customBounds.setPosition(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width * 0.2f, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 0.1);
	}

	ObjectMonster::LateUpdate(dt);
}

void BossCarnation::FaSfx()
{
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_top_laser_attack_start.wav");
}

void BossCarnation::FaIng()
{
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_top_laser_attack_hold_loop.wav");
}

void BossCarnation::FaEnd()
{
	SOUND_MGR.PauseAllSfx();
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_top_laser_attack_end.wav");
}

void BossCarnation::FaHigh()
{
	SetState(State::None);
	animator.ClearEvent();
	sf::Vector2f Pos = GetPosition();
	SetPosition({ Pos.x + 160.f,Pos.y });
	animator.Play("animations/carnationBossFa_High.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), 1, std::bind(&BossCarnation::FaSfx, this));
	animator.AddEvent(animator.GetCurrentCilpId(), 20, std::bind(&BossCarnation::FaIng, this));
	animator.AddEvent(animator.GetCurrentCilpId(), 36, std::bind(&BossCarnation::FaEnd, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));
}

void BossCarnation::FaLow()
{
	SetState(State::None);
	animator.ClearEvent();
	sf::Vector2f Pos = GetPosition();
	SetPosition({ Pos.x + 160.f,Pos.y + 20.f });
	animator.Play("animations/carnationBossFa_Low.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), 1, std::bind(&BossCarnation::FaSfx, this));
	animator.AddEvent(animator.GetCurrentCilpId(), 20, std::bind(&BossCarnation::FaIng, this));
	animator.AddEvent(animator.GetCurrentCilpId(), 36, std::bind(&BossCarnation::FaEnd, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));
}

void BossCarnation::Creating()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/carnationBossCreating.csv");
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_pot_hands_start.wav");
	animator.AddEvent("animations/carnationBossCreating.csv", 20, std::bind(&BossCarnation::CreatingEffect, this));
	animator.AddEvent("animations/carnationBossCreating.csv", 54, std::bind(&BossCarnation::CreatingEffect, this));
	animator.AddEvent("animations/carnationBossCreating.csv", 86, std::bind(&BossCarnation::CreatingEffect, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));
}

void BossCarnation::CreatingEffect()
{
	EffectCarnationCreating::Create({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.3f,sprite.getPosition().y - sprite.getGlobalBounds().height*0.5f}, {1.f, 0.f}, scene);
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_pot_hands_open.wav");
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
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_gattling_loop.wav");
	EffectCarnationFireSeed::Create({ sprite.getPosition().x - sprite.getGlobalBounds().width * 0.1f -10.f,sprite.getPosition().y - sprite.getGlobalBounds().height * 0.9f }, { 1.f,0.f }, scene);
}

void BossCarnation::FireSeed()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/carntionBossFireSeed.csv");
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_gattling_start.wav");
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

	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame()-1, std::bind(&BossCarnation::StopFireSeedSfx, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));
}

void BossCarnation::StopFireSeedSfx()
{
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_gattling_end.wav");
}

void BossCarnation::AddSeed()
{
	int rnadom = Utils::RandomRange(0, 101);
	if (rnadom <= 20)
	{
		BulletCarnationFireSeed::Create({ position.x - Utils::RandomRange(0.f,800.f)-200, position.y - 800 }, { 0.f , 1.f }, scene, 1);
	}
	else if (rnadom <= 60)
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
	animator.AddEvent(animator.GetCurrentCilpId(), 2, std::bind(&BossCarnation::IntroSfx, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::Idle, this));
	
}

void BossCarnation::IntroSfx()
{
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_intro_yell.wav");
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
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_man_phaseOneTwo_transition.wav");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame()-7, std::bind(&BossCarnation::CreateFinalVine, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::FinalIdle, this));
}

void BossCarnation::CreateFinalVine()
{
	BulletCarnationFinalVine::Create({ position.x - sprite.getGlobalBounds().width + 250.f, 0}, {1.f , 0.f}, scene);
}

void BossCarnation::FirePollen()
{
	int rnadom = Utils::RandomRange(0, 101);
	if (rnadom <= 20)
	{
		BulletCarnationPollen::Create({ position.x + sprite.getGlobalBounds().width * 0.1f - 250.f, position.y - sprite.getGlobalBounds().height * 0.6f}, {-1.f , 1.f}, scene, 1);
	}
	else
	{
		BulletCarnationPollen::Create({ position.x + sprite.getGlobalBounds().width* 0.1f - 250.f, position.y - sprite.getGlobalBounds().height * 0.6f }, { -1.f , 1.f }, scene, 0);
	}
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
	SetPosition({ Pos.x - 20.f,Pos.y - 20.f });
	animator.Play("animations/carnationFiringPollen.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), 12, std::bind(&BossCarnation::FirePollen, this));
	animator.AddEvent(animator.GetCurrentCilpId(), 34, std::bind(&BossCarnation::FirePollen, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarnation::FinalIdle, this));
}

void BossCarnation::FinalAttackPlayForm()
{
	int random = std::rand() % 6;
	if (random == 0)
	{
		BulletCarnationFinalPlatForm::Create({ scene->GetWorldView().getCenter().x - viewSize.x * 0.01f / 3.f , 0 }, { 1.f , -1.f }, scene);
	}
	else if (random == 1)
	{
		BulletCarnationFinalPlatForm::Create({ scene->GetWorldView().getCenter().x - viewSize.x * 0.61f / 3.f , 0 }, { 1.f , -1.f }, scene);
	}
	else if (random == 2)
	{
		BulletCarnationFinalPlatForm::Create({ scene->GetWorldView().getCenter().x - viewSize.x * 1.21f / 3.f , 0 }, { 1.f , -1.f }, scene);
	}
	else if (random == 3)
	{
		BulletCarnationFinalPlatForm::Create({ scene->GetWorldView().getCenter().x - viewSize.x * 0.01f / 3.f , 0 }, { 1.f , -1.f }, scene);
		BulletCarnationFinalPlatForm::Create({ scene->GetWorldView().getCenter().x - viewSize.x * 0.61f / 3.f , 0 }, { 1.f , -1.f }, scene);
	}
	else if (random == 4)
	{
		BulletCarnationFinalPlatForm::Create({ scene->GetWorldView().getCenter().x - viewSize.x * 0.01f / 3.f , 0 }, { 1.f , -1.f }, scene);
		BulletCarnationFinalPlatForm::Create({ scene->GetWorldView().getCenter().x - viewSize.x * 1.21f / 3.f , 0 }, { 1.f , -1.f }, scene);
	}
	else if (random == 5)
	{
		BulletCarnationFinalPlatForm::Create({ scene->GetWorldView().getCenter().x - viewSize.x * 0.61f / 3.f , 0 }, { 1.f , -1.f }, scene);
		BulletCarnationFinalPlatForm::Create({ scene->GetWorldView().getCenter().x - viewSize.x * 1.21f / 3.f , 0 }, { 1.f , -1.f }, scene);
	}
}

void BossCarnation::Death()
{
	isAlive = false;
	SetState(State::None);
	sceneGame->SetStatus(SceneGame::Status::Victory);
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

sf::RectangleShape BossCarnation::GetCustomBounds() const
{
	return customBounds;
}