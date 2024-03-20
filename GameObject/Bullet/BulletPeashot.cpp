#include "pch.h"
#include "BulletPeashot.h"
#include "Effect/EffectPeashot.h"

BulletPeashot::BulletPeashot(const std::string& name)
	:ObjectBullet(name)
{
}

void BulletPeashot::Init()
{
	animator.SetTarget(&sprite);
	if (rand() % 2 == 0)
	{
		animator.SetCurrentCilp("animations/peashotIntroA.csv");
	}
	else
	{
		animator.SetCurrentCilp("animations/peashotIntroB.csv");
	}
	animator.Play();
	animator.PlayQueue("animations/peashotMain.csv");
	SetSpeed(1200.f);
	SetRange(3000.f);
	type = Type::Straight;
	ObjectBullet::Init();
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
	bp->SetPosition(pos + direction * (bp->sprite.getLocalBounds().width - bp->GetOrigin().x) * bp->GetScale().x);
	return bp;
}
