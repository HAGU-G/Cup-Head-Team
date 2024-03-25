#include "pch.h"
#include "BulletCarnationPurpleSeed.h"
#include "SceneGame.h"

BulletCarnationPurpleSeed::BulletCarnationPurpleSeed(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationPurpleSeed* BulletCarnationPurpleSeed::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarnationPurpleSeed* bcp = new BulletCarnationPurpleSeed();
	bcp->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcp);
	return bcp;
}

void BulletCarnationPurpleSeed::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
}

void BulletCarnationPurpleSeed::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	animator.Play("animations/carnationSeedPurpleCreater.csv");
	SetSpeed(0.f);
	SetRange(100.f);
	type = Type::Straight;
	maxHp = 20;
	hp = 20;
	ObjectBullet::Init();
}

void BulletCarnationPurpleSeed::SetRotation(float value)
{
	ObjectBullet::SetRotation(value - 45.f);
}

void BulletCarnationPurpleSeed::OnDie()
{
	ObjectBullet::OnDie();
}

sf::FloatRect BulletCarnationPurpleSeed::GetCustomBounds() const
{
	return customBounds;
}
