#include "pch.h"
#include "BulletPotatoShoot.h"
#include "SceneGame.h"

BulletPotatoShoot::BulletPotatoShoot(const std::string& name)
	:ObjectBullet(name)
{
}

BulletPotatoShoot* BulletPotatoShoot::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletPotatoShoot* bps = new BulletPotatoShoot();
	bps->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bps);
	return bps;
}

void BulletPotatoShoot::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds.setPosition(position);
}

void BulletPotatoShoot::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	animator.SetTarget(&sprite);
	animator.Play("animations/potatoShoot1.csv");
	SetCustomBounds(0.8f, 0.8f, Origins::MC);
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

sf::RectangleShape BulletPotatoShoot::GetCustomBounds() const
{
	return customBounds;
}
