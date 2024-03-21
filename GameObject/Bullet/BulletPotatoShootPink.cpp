#include "pch.h"
#include "BulletPotatoShootPink.h"

BulletPotatoShootPink::BulletPotatoShootPink(const std::string& name)
	:ObjectBullet(name)
{
}

BulletPotatoShootPink* BulletPotatoShootPink::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletPotatoShootPink* bps = new BulletPotatoShootPink();
	bps->CreateInit(pos, direction, scene);
	return bps;
}

void BulletPotatoShootPink::Init()
{
	ObjectBullet::Init();
	animator.SetTarget(&sprite);
	animator.Play("animations/potatoShootPink.csv");
	SetSpeed(600.f);
	SetRange(1200.f);
	type = Type::Straight;
	ObjectBullet::Init();
}

void BulletPotatoShootPink::OnCreate()
{
}

void BulletPotatoShootPink::OnDie()
{
	ObjectBullet::OnDie();
}
