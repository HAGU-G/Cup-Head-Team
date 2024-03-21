#include "pch.h"
#include "BulletPotatoShoot.h"

BulletPotatoShoot::BulletPotatoShoot(const std::string& name)
	:ObjectBullet(name)
{
}

BulletPotatoShoot* BulletPotatoShoot::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletPotatoShoot* bps = new BulletPotatoShoot();
	bps->CreateInit(pos, direction, scene);
	return bps;
}

void BulletPotatoShoot::Init()
{
	ObjectBullet::Init();
	animator.SetTarget(&sprite);
	animator.Play("animations/potatoShoot1.csv");
	SetSpeed(600.f);
	SetRange(1200.f);
	type = Type::Straight;
	ObjectBullet::Init();
}

void BulletPotatoShoot::OnCreate()
{
}

void BulletPotatoShoot::OnDie()
{
	ObjectBullet::OnDie();
}
