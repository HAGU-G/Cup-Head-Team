#include "pch.h"
#include "BulletCarnationPinkSeed.h"
#include "SceneGame.h"
#include "BulletCarnationPinkCreaterAttack.h"
#include "Effect/EffectCarnationPinkDie.h"

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
	SetCustomBounds(1.f, 1.f, Origins::MC);
	customBounds.setPosition(position);
	if (hp <= 0)
	{
		EffectCarnationPinkDie::Create({ position.x - sprite.getGlobalBounds().width * 0.4f,position.y - sprite.getGlobalBounds().height * 0.45f }, { 1.f,0.f }, scene);
		OnDie();
	}
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
	isAlive = false;
	scene->RemoveGo(this);
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

sf::RectangleShape BulletCarnationPinkSeed::GetCustomBounds() const
{
	return customBounds;
}


void BulletCarnationPinkSeed::SetRotation(float value)
{
	ObjectBullet::SetRotation(value + 90.f);
}
