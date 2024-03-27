#include "pch.h"
#include "BossCarrot.h"
#include "Bullet/BulletCarrotBoom.h"
#include "Bullet/BulletCarrotBoomSmall.h"
#include "Bullet/BulletCarrotRing.h"
#include "Effect/ObjectEffect.h"

BossCarrot::BossCarrot(const std::string& name)
	:ObjectMonster(name)
{
	hp = maxHp = 475;
}

BossCarrot::~BossCarrot()
{
	Release();
}

void BossCarrot::Init()
{
	ObjectMonster::Init();
	sprite.setScale(1.15f, 1.15f);
	shootEyes.setScale(sprite.getScale());
	soundMindMeld.setBuffer(RES_MGR_SOUND_BUFFER.Get("resource/Sprite/stage01/carrot/sfx_level_veggies_Carrot_MindMeld_Loop.wav"));
	soundMindMeld.setLoop(true);
}

void BossCarrot::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	animator.SetTarget(&sprite);
	eyeAnimator.SetTarget(&shootEyes);
	eyeAnimator.Play("animations/carrotShootEyes.csv");
	Intro();
}

void BossCarrot::Update(float dt)
{
	soundMindMeld.setVolume(SOUND_MGR.GetSfxVolume());
	ObjectMonster::Update(dt);
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
	case State::Pattern1:
		patternTimer += dt;
		if (patternTimer >= patternInterval)
		{
			patternTimer = 0.f;
			SetState(State::Pattern2);
		}
		else if (BoomTimer(dt))
		{
			BulletCarrotBoom::Create(position + sf::Vector2f((rand() % 3 - 1) * FRAMEWORK.GetWindowSize().x / 4.f, -1.0f * GetGlobalBounds().height), { 0.f, 1.f }, scene);
		}
		break;
	case State::Ring:
		eyeAnimator.Update(dt);
		patternTimer += dt;
		if (patternTimer >= patternInterval)
		{
			patternTimer = 0.f;
			SetState(State::Pattern2);
		}
		else if (RingTimer(dt))
		{
			ObjectEffect* oe = new ObjectEffect("EffectCarrotRingIntro");
			oe->CreateInit(shootEyes.getPosition() + sf::Vector2f(0.f, -shootEyes.getGlobalBounds().height * 0.6f), { 1.f, 0.f }, scene);
			oe->GetAniamtor().Play("animations/carrotRingIntro.csv");
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame() - 10, std::bind(&BossCarrot::SetTargetDirection, this));
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame() - 9, std::bind(&BossCarrot::ShootRing, this));
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame() - 7, std::bind(&BossCarrot::ShootRing, this));
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame() - 5, std::bind(&BossCarrot::ShootRing, this));
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame() - 3, std::bind(&BossCarrot::ShootRing, this));
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame() - 1, std::bind(&BossCarrot::ShootRing, this));
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
		}
		break;
	default:
		break;
	}
}

void BossCarrot::LateUpdate(float dt)
{
	ObjectMonster::LateUpdate(dt);
	shootEyes.setPosition(position + sf::Vector2f(-5.f, -sprite.getGlobalBounds().getSize().y * 1.8f / 3.f));
	SetCustomBounds(0.5f, 0.3f, Origins::MC);
	customBounds.setPosition(shootEyes.getPosition());


	if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
	{
		OnDamage(100);
	}
}

void BossCarrot::Release()
{
	soundMindMeld.stop();
	ObjectMonster::Release();
}

void BossCarrot::Draw(sf::RenderTexture& window)
{
	ObjectMonster::Draw(window);
	if (state == State::Ring)
	{
		if (useRenderStates) { window.draw(shootEyes, renderStates); }
		else { window.draw(shootEyes); }
	}
}

void BossCarrot::Intro()
{
	SetState(State::None);
	soundMindMeld.play();
	ObjectEffect* front = new ObjectEffect("CarrotIntroBack");
	front->sortLayer = -3;
	SOUND_MGR.PlaySfx("resource/Sprite/stage01/carrot/sfx_level_veggies_Carrot_Rise.wav");
	front->SetScale({ 0.9f, 0.9f });
	front->CreateInit(position + sf::Vector2f(0.f, scene->GetWorldView().getSize().y * 0.09f), { 1.f,0.f }, scene);
	front->GetAniamtor().Play("animations/potatoIntroFront.csv");
	front->GetAniamtor().AddEvent(front->GetAniamtor().GetCurrentCilpId(), 8,
		[this, front]()
		{
			ObjectEffect* back = new ObjectEffect("CarrotIntroFront");
			back->SetScale({ 1.1f, 1.1f });
			back->sortLayer = -4;
			back->CreateInit(position + sf::Vector2f(0.f, scene->GetWorldView().getSize().y * 0.03f), { 1.f,0.f }, scene);
			back->GetAniamtor().Play("animations/potatoIntroBack.csv");
			animator.ClearEvent();
			animator.Play("animations/carrotIntro.csv");
			animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarrot::Pattern1, this));
			patternTimer = 2.f;
		});


}

void BossCarrot::Pattern1()
{
	SetState(State::Pattern1);
}

void BossCarrot::Ring()
{
	SetState(State::Ring);
}

void BossCarrot::ShootRing()
{
	BulletCarrotRing::Create(ringCreatePos, targetDirection, scene);
}

void BossCarrot::SetTargetDirection()
{
	ringCreatePos = shootEyes.getPosition() + sf::Vector2f(0.f, -shootEyes.getGlobalBounds().height * 0.6f);
	GameObject* player = scene->FindGo("Player");
	if (player)
	{
		targetDirection = player->GetPosition() - ringCreatePos;
	}
}

void BossCarrot::Death()
{
	soundMindMeld.stop();
	scene->RemoveGo(scene->FindGo("EffectCarrotRingIntro"));
	SOUND_MGR.PlaySfx("resource/Sprite/stage01/carrot/sfx_level_veggies_Carrot_Die.wav");
	SOUND_MGR.PlaySfx("resource/FightText/sfx_level_knockout_boom_01.wav");
	isAlive = false;
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/carrotDeath.csv");
}

void BossCarrot::OnDie()
{
	isAlive = false;
	scene->RemoveGo(this);
}

void BossCarrot::SetState(State state)
{
	this->state = state;
	switch (state)
	{

	case BossCarrot::State::Pattern1:
		patternInterval = 13.0f;
		animator.Play("animations/carrotIdle.csv");
		SOUND_MGR.PlaySfx("resource/Sprite/stage01/carrot/sfx_level_veggies_Carrot_MindMeld_Start.wav");
		BulletCarrotBoomSmall::Create(position + sf::Vector2f(scene->GetWorldView().getSize().x / 4.f, 1.0f * GetGlobalBounds().height), { 0.f, -1.f }, scene);
		BulletCarrotBoomSmall::Create(position + sf::Vector2f(-scene->GetWorldView().getSize().x / 3.5f, 1.5f * GetGlobalBounds().height), { 0.f, -1.f }, scene);
		BulletCarrotBoomSmall::Create(position + sf::Vector2f(scene->GetWorldView().getSize().x / 3.f, 2.0f * GetGlobalBounds().height), { 0.f, -1.f }, scene);
		BulletCarrotBoomSmall::Create(position + sf::Vector2f(-scene->GetWorldView().getSize().x / 2.5f, 2.5f * GetGlobalBounds().height), { 0.f, -1.f }, scene);
		preState = State::Pattern1;
		break;
	case BossCarrot::State::Pattern2:
		patternInterval = ringInterval * 2.9f;
		animator.ClearEvent();
		if (preState == State::Ring)
		{
			animator.Play("animations/carrotTransitionReverse.csv");
			animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarrot::Pattern1, this));
		}
		else
		{
			animator.Play("animations/carrotTransition.csv");
			animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarrot::Ring, this));
		}
		preState = State::Pattern2;
		break;
	case BossCarrot::State::Ring:
		animator.Play("animations/carrotShootBody.csv");
		eyeAnimator.Play("animations/carrotShootEyes.csv");
		preState = State::Ring;
		break;
	default:
		break;
	}
}

bool BossCarrot::PatternTimer(float dt)
{
	patternTimer += dt;
	if (patternTimer >= patternInterval)
	{
		patternTimer = 0.f;
		return true;
	}
	return false;
}

bool BossCarrot::BoomTimer(float dt)
{
	boomTimer += dt;
	if (boomTimer >= boomInterval)
	{
		boomTimer = 0.f;
		return true;
	}
	return false;
}

bool BossCarrot::RingTimer(float dt)
{
	ringTimer += dt;
	if (ringTimer >= ringInterval)
	{
		ringTimer = 0.f;
		return true;
	}
	return false;
}

sf::RectangleShape BossCarrot::GetCustomBounds() const
{
	return customBounds;
}
