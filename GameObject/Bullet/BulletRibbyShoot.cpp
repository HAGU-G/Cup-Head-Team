#include "pch.h"
#include "BulletRibbyShoot.h"
#include "SceneGame.h" 

BulletRibbyShoot::BulletRibbyShoot(const std::string& name)
	:ObjectBullet(name)
{
}

BulletRibbyShoot* BulletRibbyShoot::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletRibbyShoot* brs = new BulletRibbyShoot();
	brs->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(brs);
	return brs;
}

void BulletRibbyShoot::Update(float dt)
{
	ObjectBullet::Update(dt);

	auto bounds = sprite.getGlobalBounds();
	float shrinkFactor = 0.5f;
	float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
	float heightReduction = bounds.height * (1 - shrinkFactor) / 2;
	customBounds = sf::FloatRect(bounds.left + widthReduction, bounds.top, bounds.width * shrinkFactor, bounds.height);
}

void BulletRibbyShoot::Init()
{
	ObjectBullet::Init();
	
	owner = Owner::Enemy;
	animator.SetTarget(&sprite);
	animator.Play("animations/RibbyShoot1.csv");
	SetSpeed(600.f);
	SetRange(1200.f);
	type = Type::Straight;
}

void BulletRibbyShoot::OnCreate()
{
}

void BulletRibbyShoot::OnDie()
{
	ObjectBullet::OnDie();
}

sf::FloatRect BulletRibbyShoot::GetCustomBounds() const
{
	return customBounds;
}
