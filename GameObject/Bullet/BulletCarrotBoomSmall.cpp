#include "pch.h"
#include "BulletCarrotBoomSmall.h"
#include "Effect/ObjectEffect.h"
#include <SceneGame.h>

BulletCarrotBoomSmall::BulletCarrotBoomSmall(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarrotBoomSmall* BulletCarrotBoomSmall::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarrotBoomSmall* bcbs = new BulletCarrotBoomSmall();
	bcbs->sortLayer = -11;
	bcbs->CreateInit(pos, direction, scene);
	return bcbs;
}

void BulletCarrotBoomSmall::Update(float dt)
{
	ObjectBullet::Update(dt);
}

void BulletCarrotBoomSmall::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	animator.Play("animations/carrotBoomSmall.csv");
	SetSpeed(400.f);
	SetRange(8000.f);
	type = Type::Straight;
}
void BulletCarrotBoomSmall::LateUpdate(float dt)
{
	ObjectMonster::LateUpdate(dt);
	if (moveDistance >= range)
	{
		if (isAlive)
		{
			isAlive = false;
		}
		else
		{
			OnDie();
		}
	}
}

void BulletCarrotBoomSmall::SetRotation(float value)
{
	ObjectBullet::SetRotation(value);
	sprite.setRotation(value + 90.f);
}

void BulletCarrotBoomSmall::Flip()
{
	if (direction.y != 0.f)
	{
		SetScale({ abs(direction.y) / direction.y,1.f  });
	}
}