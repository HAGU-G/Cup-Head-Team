#include "pch.h"
#include "BulletPotatoShootPink.h"
#include "SceneGame.h"

BulletPotatoShootPink::BulletPotatoShootPink(const std::string& name)
	:ObjectBullet(name)
{
}

BulletPotatoShootPink* BulletPotatoShootPink::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletPotatoShootPink* bps = new BulletPotatoShootPink();
	bps->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bps);
	return bps;
}

void BulletPotatoShootPink::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds.setPosition(position);
}

void BulletPotatoShootPink::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	animator.SetTarget(&sprite);
	animator.Play("animations/potatoShootPink.csv");
	SetCustomBounds(0.8f, 0.8f, Origins::MC);
	SetSpeed(600.f);
	SetRange(1200.f);
	type = Type::Straight;
	isPink = true;
}

void BulletPotatoShootPink::OnCreate()
{
}

void BulletPotatoShootPink::OnDie()
{
	ObjectBullet::OnDie();
}

sf::RectangleShape BulletPotatoShootPink::GetCustomBounds() const
{
	return customBounds;
}
