#include "pch.h"
#include "BulletCarnationPinkSeed.h"
#include "SceneGame.h"
#include "BulletCarnationPinkCreaterAttack.h"

BulletCarnationPinkSeed::BulletCarnationPinkSeed(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationPinkSeed* BulletCarnationPinkSeed::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarnationPinkSeed* bcp = new BulletCarnationPinkSeed();
	bcp->CreateInit(pos, direction, scene);
	bcp->isPink = false;
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcp);
	return bcp;
}

void BulletCarnationPinkSeed::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
	if (sprite.getPosition().y <= -400)
	{
		timerStart = true;
	}
	if (sprite.getPosition().y <= -500)
	{
		if (timerStart)
		{
			attackTimer += dt;
			if (attackTimer >= 7.f)
			{
				Stop();
				attackTimer = 0;
				timerStart = false;
			}
		}
		SetDirection({ 1.f,0.f });
		if (sprite.getPosition().x >= 300)
		{
			right = true;
			left = false;
		}
		else if (sprite.getPosition().x <= -500)
		{
			right = false;
			left = true;
		}
		if (right)
		{
			direction.x = -1;
			SetDirection(direction);
		}
		else if (left)
		{
			direction.x = 1;
			SetDirection(direction);
		}
	}
}

void BulletCarnationPinkSeed::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	animator.Play("animations/carnationBossCreatPinkCreater.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationPinkSeed::Move, this));
	SetSpeed(0);
	SetRange(15000.f);
	type = Type::Straight;
	SetRotateSpeed(400.f);
	maxHp = 50;
	hp = 50;
}

void BulletCarnationPinkSeed::OnDie()
{
	//ObjectEffect* oe = new ObjectEffect("EffectCarrotBoom");
	//oe->CreateInit(position, direction, scene);
	//oe->GetAniamtor().Play("animations/carrotBoomDeath.csv");
	//oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
	ObjectBullet::OnDie();
}

void BulletCarnationPinkSeed::Move()
{
	moveSpeed = 300.f;
	SetSpeed(moveSpeed);
	animator.Play("animations/carnationBossCreatPinkCreaterMove.csv");
}

void BulletCarnationPinkSeed::Stop()
{
	animator.ClearEvent();
	animator.Play("animations/carnationBossCreatPinkCreaterAttack.csv");
	SetSpeed(0.f);
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationPinkSeed::Attack, this));
	
}

void BulletCarnationPinkSeed::Attack()
{
	BulletCarnationPinkCreaterAttack::Create({ position.x ,position.y }, { 0.f,-1.f }, scene);
	animator.Play("animations/carnationBossCreatPinkCreaterAttackReturn.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationPinkSeed::TimerStart, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationPinkSeed::Move, this));
}

void BulletCarnationPinkSeed::Flip()
{
	if (direction.y != 0.f)
	{
		SetScale({ direction.y / direction.y, 1.f });
	}
}

sf::FloatRect BulletCarnationPinkSeed::GetCustomBounds() const
{
	return customBounds;
}


void BulletCarnationPinkSeed::SetRotation(float value)
{
	ObjectBullet::SetRotation(value + 90.f);
}
