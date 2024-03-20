#include "pch.h"
#include "BulletPeashot.h"
#include "Effect/ObjectEffect.h"

BulletPeashot::BulletPeashot(const std::string& name)
	:ObjectBullet(name)
{
}

void BulletPeashot::Init()
{
	SetTexture("resource/Sprite/peashot/weapon_peashot_intro_b_0001.png");
	SetOrigin(Origins::ML);
	SetSpeed(1200.f);
	SetRange(3000.f);
	type = Type::Straight;
	ObjectBullet::Init();
}

void BulletPeashot::SetPosition(const sf::Vector2f& pos)
{
	ObjectBullet::SetPosition(pos);
	bound.setPosition(pos + direction * sprite.getLocalBounds().width * 0.75f * GetScale().x);
}

void BulletPeashot::OnCreate()
{
	ObjectEffect::Create(position, direction, scene);
}

void BulletPeashot::OnDie()
{
	ObjectEffect::Create(bound.getPosition(), direction, scene);
}

BulletPeashot* BulletPeashot::Create(const sf::Vector2f& pos, Direction direction, Scene* scene)
{
	return Create(pos, Utils::DirectionConversion(direction), scene);
}

BulletPeashot* BulletPeashot::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletPeashot* bp = new BulletPeashot();
	bp->CreateInit(pos, direction, scene);
	return bp;
}
