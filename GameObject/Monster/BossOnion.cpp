#include "pch.h"
#include "BossOnion.h"
#include "SceneGame.h"
#include "Effect/EffectOnionTears.h"
#include "Bullet/BulletOnionTear.h"

BossOnion::BossOnion(const std::string& name)
	:ObjectMonster(name)
{
}

void BossOnion::Init()
{
	ObjectMonster::Init();
	sprite.setScale(1.f / 1.1f, 1.f / 1.1f);
	hasHitBox = true;
	soundCrying.setBuffer(RES_MGR_SOUND_BUFFER.Get("resource/Sprite/stage01/onion/sfx_level_veggies_Onion_Crying.wav"));
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
	soundCrying.setVolume(SOUND_MGR.GetSfxVolume());
	ObjectMonster::Update(dt);
	if (hp == 0)
	{
		BossDieEffect(dt);
		if (state < State::None)
		{
			Death();
		}
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
				BulletOnionTear::Create(position + sf::Vector2f(tearSide * Utils::RandomRange(sprite.getGlobalBounds().width * 0.6f, scene->GetWorldView().getSize().x * 0.5f),
					-2.f * sprite.getGlobalBounds().height), { 0.f , 1.f }, scene, true);
			}
			else
			{
				BulletOnionTear::Create(position + sf::Vector2f(tearSide * Utils::RandomRange(sprite.getGlobalBounds().width * 0.6f, scene->GetWorldView().getSize().x * 0.5f),
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
	SetCustomBounds(0.5f, 0.8f, Origins::BC);
	customBounds.setPosition(position);
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
	ObjectEffect* front = new ObjectEffect("OnionIntroBack");
	SOUND_MGR.PlaySfx("resource/Sprite/stage01/onion/sfx_level_veggies_Onion_Rise.wav");
	front->SetScale({ 1.1f, 1.1f });
	front->CreateInit(position + sf::Vector2f(0.f, scene->GetWorldView().getSize().y * 0.09f), { 1.f,0.f }, scene);
	front->GetAniamtor().Play("animations/potatoIntroFront.csv");
	front->GetAniamtor().AddEvent(front->GetAniamtor().GetCurrentCilpId(), 8,
		[this, front]()
		{
			ObjectEffect* back = new ObjectEffect("OnionIntroFront");
			back->SetScale({ 1.1f, 1.1f });
			back->sortLayer = -1;
			back->CreateInit(position + sf::Vector2f(0.f, scene->GetWorldView().getSize().y * 0.03f), { 1.f,0.f }, scene);
			back->GetAniamtor().Play("animations/potatoIntroBack.csv");
			animator.ClearEvent();
			animator.Play("animations/onionIntro.csv");
			animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossOnion::Idle, this));
			patternTimer = 2.f;
		});

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
	soundCrying.play();
	EffectOnionTears::Create(position + sf::Vector2f(sprite.getGlobalBounds().width / 25.f, -sprite.getGlobalBounds().height * 5.f / 8.f), { 1.f, 0.f }, scene, cryingDuration * 1.15f);
	EffectOnionTears::Create(position + sf::Vector2f(-sprite.getGlobalBounds().width * 2.f / 25.f, -sprite.getGlobalBounds().height * 5.f / 8.f), { -1.f, 0.f }, scene, cryingDuration * 1.15f);
}

void BossOnion::Death()
{
	scene->RemoveGo(scene->FindGo("OnionTears"));
	scene->RemoveGo(scene->FindGo("OnionTears"));
	soundCrying.stop();
	SOUND_MGR.PlaySfx("resource/Sprite/stage01/onion/sfx_level_veggies_Onion_Die.wav");
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
	scene->RemoveGo(scene->FindGo("OnionIntroBack"));
	scene->RemoveGo(scene->FindGo("OnionIntroFront"));
	scene->RemoveGo(this);
}

bool BossOnion::TearTimer(float dt)
{
	tearTimer += dt;
	if (tearTimer >= tearInterval)
	{
		tearTimer = 0.f;
		tearInterval = Utils::RandomRange(0.2f,0.6f);
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
		animator.ClearEvent();
		if (preState == State::Crying)
		{
			animator.Play("animations/onionCryingReverse.csv");
			animator.AddEvent("animations/onionCryingReverse.csv", 11, [this]() { soundCrying.stop(); });
			animator.PlayQueue("animations/onionCrying.csv");
		}
		else
		{
			animator.Play("animations/onionCrying.csv");
		}
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

sf::RectangleShape BossOnion::GetCustomBounds() const
{
	return customBounds;
}

