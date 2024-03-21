#include "pch.h"
#include "BossCarrot.h"
#include "Bullet/BulletCarrotBoom.h"
#include "Bullet/BulletCarrotRing.h"
#include "Effect/ObjectEffect.h"

BossCarrot::BossCarrot(const std::string& name)
	:ObjectMonster(name)
{
}

void BossCarrot::Init()
{
	ObjectMonster::Init();
	sprite.setScale(1.3f, 1.3f);
	RES_MGR_TEXTURE.Load("resource/carrotDeath.png");
	RES_MGR_TEXTURE.Load("resource/carrotIdle.png");
	RES_MGR_TEXTURE.Load("resource/carrotIntro.png");
	RES_MGR_TEXTURE.Load("resource/carrotShootBody.png");
	RES_MGR_TEXTURE.Load("resource/carrotShootEyes.png");
	RES_MGR_TEXTURE.Load("resource/carrotRing.png");
	RES_MGR_TEXTURE.Load("resource/carrotBoom.png");
	RES_MGR_TEXTURE.Load("resource/carrotRingDeath.png");
	RES_MGR_TEXTURE.Load("resource/carrotBoomDeath.png");
	RES_MGR_TEXTURE.Load("resource/carrotRingIntro.png");
}

void BossCarrot::Reset()
{
	ObjectMonster::Reset();
	scene = SCENE_MGR.GetCurrentScene();
	animator.SetTarget(&sprite);
	eyeAnimator.SetTarget(&shootEyes);
	Intro();
}

void BossCarrot::Update(float dt)
{
	ObjectMonster::Update(dt);
	if (hp == 0 && state < State::None)
	{
		Death();
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
			BulletCarrotBoom::Create(position + sf::Vector2f((rand() % 3 - 1) * FRAMEWORK.GetWindowSize().x / 4.f, -1.5f * GetGlobalBounds().height), { 0.f, 1.f }, scene);
		}
		break;
	case State::Ring:
		eyeAnimator.Update(dt);
		patternTimer += dt;
		shootEyes.setPosition(position + sf::Vector2f(0.f, -sprite.getGlobalBounds().getSize().y * 1.8f / 3.f));
		if (patternTimer >= patternInterval)
		{
			patternTimer = 0.f;
			SetState(State::Pattern2);
		}
		else if (RingTimer(dt))
		{
			ObjectEffect* oe = new ObjectEffect("EffectCarrotRingIntro");
			oe->CreateInit(shootEyes.getPosition(), {1.f, 0.f}, scene);
			oe->GetAniamtor().Play("animations/carrotRingIntro.csv");
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame()-1, std::bind(&BossCarrot::ShootRing, this));
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame()-3, std::bind(&BossCarrot::ShootRing, this));
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame()-5, std::bind(&BossCarrot::ShootRing, this));
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame()-7, std::bind(&BossCarrot::ShootRing, this));
			oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame()-9, std::bind(&BossCarrot::ShootRing, this));
		}
		break;
	default:
		break;
	}
}

void BossCarrot::LateUpdate(float dt)
{
	ObjectMonster::LateUpdate(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		OnDamage(10);
	}
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
	animator.ClearEvent();
	animator.Play("animations/carrotIntro.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossCarrot::Pattern1, this));

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
	BulletCarrotRing::Create(shootEyes.getPosition(), { 1.f,1.f }, scene);
}

void BossCarrot::Death()
{
	SetState(State::None);
	animator.ClearEvent();
	animator.Play("animations/carrotDeath.csv");
}

void BossCarrot::OnDie()
{
	scene->RemoveGo(this);
}

void BossCarrot::SetState(State state)
{
	this->state = state;
	switch (state)
	{

	case BossCarrot::State::Pattern1:
		animator.Play("animations/carrotIdle.csv");
		preState = State::Pattern1;
		break;
	case BossCarrot::State::Pattern2:
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

bool BossCarrot::CollisionCheck()
{
	return true;
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
