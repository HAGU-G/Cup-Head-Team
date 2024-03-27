#include "pch.h"
#include "BossCroaks.h"
#include "SceneGame.h"
#include "Bullet/BulletCroaksFirefly.h"
#include "Effect/ObjectEffect.h"
#include "Player.h"

BossCroaks::BossCroaks(const std::string& name)
	:ObjectMonster(name)
{
}

void BossCroaks::Init()
{
	ObjectMonster::Init();
	hp = maxHp = 1400;
	hasHitBox = true;

	soundFan.setBuffer(RES_MGR_SOUND_BUFFER.Get("resource/Sprite/stage03/sfx_frogs_tall_fan_attack_loop_01.wav"));
	soundFan.setLoop(true);
}

void BossCroaks::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	animator.SetTarget(&sprite);
	SetPosition({ 300,0 });
	Intro();

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
}

void BossCroaks::Release()
{
	soundFan.stop();
	ObjectMonster::Release();
}

void BossCroaks::Update(float dt)
{

	soundFan.setVolume(SOUND_MGR.GetSfxVolume());
	ObjectMonster::Update(dt);
	deltatime = dt;
	if (hp == 0)
	{
		BossDieEffect(dt);
		if (state < State::None)
		{
			Death();
		}
	}

	if (animator.GetCurrentCilpId() == "animations/CroaksFanLoop.csv")
	{
		Fan();
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
			patternTimer = 4.5f;
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
				soundFan.stop();
				SOUND_MGR.PlaySfx("resource/Sprite/stage03/sfx_frogs_tall_fan_end_01.wav");
				animator.Play("animations/CroaksFanOutro.csv");
				animator.AddEvent("animations/CroaksFanOutro.csv", animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCroaks::Idle, this));
			}
		}
		break;
	}

	auto bounds = sprite.getGlobalBounds();
	float shrinkFactor = 0.6f;
	float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
	float heightReduction = bounds.height * (1 - 1.f) / 2;
	//customBounds = sf::FloatRect(bounds.left + widthReduction, bounds.top, bounds.width * shrinkFactor, bounds.height);
	SetCustomBounds(shrinkFactor, 1.f, Origins::TL);
	customBounds.setPosition(bounds.left + widthReduction, bounds.top + heightReduction);
}

void BossCroaks::LateUpdate(float dt)
{
	ObjectMonster::LateUpdate(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
	{
		OnDamage(100);
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
	playerPos = player->GetPosition();
	playerPos.x -= fanBackwardSpeed * deltatime;
	player->SetPosition(playerPos);
}

void BossCroaks::Shoot()
{
	if (shootCount < 3)
	{
		shootCount++;
		SOUND_MGR.PlaySfx("resource/Sprite/stage03/sfx_frogs_tall_spit_shoot_01.wav");
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
	soundFan.stop();
	isAlive = false;
	SetState(State::None);
	animator.ClearEvent();
	SOUND_MGR.PlaySfx("resource/Sprite/stage03/sfx_frogs_tall_death_03.wav");
	SOUND_MGR.PlaySfx("resource/FightText/sfx_level_knockout_boom_01.wav");
	animator.Play("animations/CroaksDeath.csv");

}

void BossCroaks::OnDie()
{
	isAlive = false;
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
	if (fanTimer >= fanDuration)
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
		SOUND_MGR.PlaySfx("resource/Sprite/stage03/sfx_frogs_tall_fan_start_01.wav");
		animator.Play("animations/CroaksFanIntro.csv");
		animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetLastFrame(), [this]() { soundFan.play(); });
		animator.PlayQueue("animations/CroaksFanLoop.csv");
		preState = State::Fan;
		break;
	case BossCroaks::State::None:
		break;
	default:
		break;
	}
}

sf::RectangleShape BossCroaks::GetCustomBounds() const
{
	return customBounds;
}
