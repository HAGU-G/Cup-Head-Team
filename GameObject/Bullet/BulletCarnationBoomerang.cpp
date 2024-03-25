#include "pch.h"
#include "BulletCarnationBoomerang.h"
#include "SceneGame.h"

BulletCarnationBoomerang::BulletCarnationBoomerang(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationBoomerang* BulletCarnationBoomerang::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarnationBoomerang* bcb = new BulletCarnationBoomerang();
	bcb->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcb);
	return bcb;
}

void BulletCarnationBoomerang::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
	if (sprite.getPosition().x <= -800)
	{
		SetPosition({ sprite.getPosition().x,-100.f });
		SetDirection({ 1.f,0.f });
	}
	fireTimer += dt;
	if (fireTimer >= 1.f)
	{
		SetSpeed(800.f);
	}
}

void BulletCarnationBoomerang::Init()
{
	ObjectBullet::Init();
	animator.Play("animations/boomerang.csv");
	SetSpeed(0.f);
	SetRange(3000.f);
	type = Type::Straight;
	SetTargetPosition({ 0.f, 300.f });
	ObjectBullet::Init();
}

void BulletCarnationBoomerang::OnDie()
{
	ObjectBullet::OnDie();
}

sf::FloatRect BulletCarnationBoomerang::GetCustomBounds() const
{
	return customBounds;
}