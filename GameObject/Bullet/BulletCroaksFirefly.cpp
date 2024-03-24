#include "pch.h"
#include "BulletCroaksFirefly.h"

BulletCroaksFirefly::BulletCroaksFirefly(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCroaksFirefly* BulletCroaksFirefly::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	return nullptr;
}

void BulletCroaksFirefly::Update(float dt)
{
	ObjectBullet::Update(dt);
}

void BulletCroaksFirefly::Init()
{
	ObjectBullet::Init();
}

void BulletCroaksFirefly::OnDie()
{
	ObjectBullet::OnDie();
}

sf::FloatRect BulletCroaksFirefly::GetCustomBounds() const
{
	return customBounds;
}
