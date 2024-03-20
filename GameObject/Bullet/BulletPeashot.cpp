#include "pch.h"
#include "BulletPeashot.h"
#include "Effect/EffectPeashot.h"

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
	//type = Type::Straight;
	type = Type::Homing;
	SetTargetPosition({ 0.f, 0.f });
	SetRotateSpeed(360.f);
	ObjectBullet::Init();
}

void BulletPeashot::SetPosition(const sf::Vector2f& pos)
{
	ObjectBullet::SetPosition(pos);
	bound.setPosition(pos + direction * sprite.getLocalBounds().width * 0.75f * GetScale().x);
}

void BulletPeashot::OnCreate()
{
	EffectPeashot::Create(position, Utils::RandomOnUnitCircle(), scene, true);
}

void BulletPeashot::OnDie()
{
	EffectPeashot::Create(bound.getPosition(), Utils::RandomOnUnitCircle(), scene, false);
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
