#include "pch.h"
#include "BossPotato.h"
#include "SceneGame.h"
#include "Bullet/BulletPotatoShoot.h"
#include "Bullet/BulletPotatoShootPink.h"
#include "Effect/ObjectEffect.h"

BossPotato::BossPotato(const std::string& name)
	:ObjectMonster(name)
{
	hp = maxHp = 360;
}

void BossPotato::Init()
{
	ObjectMonster::Init();
	sprite.setScale(1.2f, 1.2f);



	hasHitBox = true;
}

void BossPotato::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	animator.SetTarget(&sprite);
	Intro();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));
}

void BossPotato::Update(float dt)
{
	ObjectMonster::Update(dt);
	///////////////////////////////////////
	SetCustomBounds(0.4f, 0.9f, Origins::BC);
	customBounds.setPosition(position);
	//////////////////////////////////////
	if (hp == 0)
	{
		BossDieEffect(dt);
		if (state < State::None)
		{
			Death();
		}
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

	if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
	{
		OnDamage(100);
	}
}

void BossPotato::Intro()
{
	SetState(State::None);
	ObjectEffect* front = new ObjectEffect("PotatoIntroBack");
	SOUND_MGR.PlaySfx("resource/Sprite/stage01/potato/sfx_level_veggies_Potato_RiseGround.wav");
	front->SetScale({ 1.1f, 1.1f });
	front->CreateInit(position + sf::Vector2f(0.f, scene->GetWorldView().getSize().y * 0.09f), { 1.f,0.f }, scene);
	front->GetAnimator().Play("animations/potatoIntroFront.csv");
	front->GetAnimator().AddEvent(front->GetAnimator().GetCurrentCilpId(), 8,
		[this, front]()
		{
			ObjectEffect* back = new ObjectEffect("PotatoIntroFront");
			back->SetScale({ 1.1f, 1.1f });
			back->sortLayer = -1;
			back->CreateInit(position + sf::Vector2f(0.f, scene->GetWorldView().getSize().y * 0.03f), { 1.f,0.f }, scene);
			back->GetAnimator().Play("animations/potatoIntroBack.csv");
			animator.ClearEvent();
			animator.Play("animations/potatoIntro.csv");
			animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossPotato::Idle, this));
			patternTimer = 2.f;
		});
}

void BossPotato::Idle()
{
	SetState(State::Idle);
}

void BossPotato::Shoot()
{
	ObjectEffect* oe = new ObjectEffect();
	oe->CreateInit(sf::Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 6.7f / 8.f), { 1.f,0.f }, scene);
	oe->GetAnimator().Play("animations/potatoShootEffect.csv");
	oe->GetAnimator().AddEvent(oe->GetAnimator().GetCurrentCilpId(), oe->GetAnimator().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
	if (++shootCount < 4)
	{
		SOUND_MGR.PlaySfx("resource/Sprite/stage01/potato/sfx_level_veggies_Potato_Spit_00"
			+std::to_string(Utils::RandomRange(1,4)) + ".wav");
		BulletPotatoShoot::Create(sf::Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 6.7f / 8.f), { -1.f, 0.f }, scene);
	}
	else
	{
		SOUND_MGR.PlaySfx("resource/Sprite/stage01/potato/sfx_level_veggies_Potato_Spit_Worm_0"
			+ std::to_string(Utils::RandomRange(1, 3)) + ".wav");
		BulletPotatoShootPink::Create(sf::Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 6.7f / 8.f), { -1.f, 0.f }, scene);
	}
}

void BossPotato::ShootEnd()
{
	SetState(State::Pattern1);
}

void BossPotato::Death()
{
	SOUND_MGR.PlaySfx("resource/FightText/sfx_level_knockout_boom_01.wav");
	isAlive = false;
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
	scene->RemoveGo(scene->FindGo("PotatoIntroBack"));
	scene->RemoveGo(scene->FindGo("PotatoIntroFront"));
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

sf::RectangleShape BossPotato::GetCustomBounds() const
{
	return customBounds;
}
