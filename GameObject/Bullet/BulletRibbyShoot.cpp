#include "pch.h"
#include "BulletRibbyShoot.h"
#include "SceneDev3.h"
//#include "SceneGame.h"    테스트 하기위해 잠시 SceneDev3 추가 및 SceneGame 주석처리 하였음

BulletRibbyShoot::BulletRibbyShoot(const std::string& name)
	:ObjectBullet(name)
{
}

BulletRibbyShoot* BulletRibbyShoot::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletRibbyShoot* brs = new BulletRibbyShoot();
	brs->CreateInit(pos, direction, scene);
	dynamic_cast<SceneDev3*>(scene)->AddMonster(brs);
	//dynamic_cast<SceneGame*>(scene)->AddMonster(brs);
	return brs;
}

void BulletRibbyShoot::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
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
