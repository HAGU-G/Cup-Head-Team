#include "pch.h"
#include "BulletPeashot.h"

BulletPeashot::BulletPeashot(const std::string& name)
	:ObjectBullet(name)
{
}

void BulletPeashot::Init()
{
	SetTexture("resource/Sprite/peashot/weapon_peashot_intro_b_0001.png");
	SetOrigin(Origins::ML);
	SetSpeed(300.f);
	SetRange(600.f);
	ObjectBullet::Init();
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
