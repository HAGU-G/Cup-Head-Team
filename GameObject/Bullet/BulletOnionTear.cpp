#include "pch.h"
#include "BulletOnionTear.h"

BulletOnionTear::BulletOnionTear(const std::string& name)
{
}

BulletOnionTear* BulletOnionTear::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, bool isPink)
{
	BulletOnionTear* bot = new BulletOnionTear();
	bot->isPink = isPink;
	bot->CreateInit(pos, direction, scene);
	return bot;
}

void BulletOnionTear::Init()
{
	ObjectBullet::Init();
	animator.SetTarget(&sprite);
	if (isPink)
	{
		animator.Play("animations/onionTearPink.csv");
	}
	else
	{
		animator.Play("animations/onionTear.csv");
	}
	SetSpeed(600.f);
	SetRange(1200.f);
	type = Type::Straight;
	ObjectBullet::Init();
}

void BulletOnionTear::OnCreate()
{
}

void BulletOnionTear::OnDie()
{
}

void BulletOnionTear::SetRotation(float value)
{
	ObjectBullet::SetRotation(value - 90.f);
}
