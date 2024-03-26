#include "pch.h"
#include "BulletCarnationBlueSeed.h"
#include "SceneGame.h"

BulletCarnationBlueSeed::BulletCarnationBlueSeed(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationBlueSeed* BulletCarnationBlueSeed::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarnationBlueSeed* bcb = new BulletCarnationBlueSeed();
	bcb->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcb);
	return bcb;
}

void BulletCarnationBlueSeed::Update(float dt)
{
	ObjectBullet::Update(dt);
	SetCustomBounds(1.f, 1.f, Origins::MC);
	customBounds.setPosition(position);
}

void BulletCarnationBlueSeed::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	animator.Play("animations/carnationVinusCreat.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationBlueSeed::Frie, this));
	SetSpeed(0.f);
	SetRange(15000.f);
	type = Type::Homing;
	SetRotateSpeed(400.f);
	maxHp = 30;
	hp = 30;
}

void BulletCarnationBlueSeed::OnDie()
{
	//ObjectEffect* oe = new ObjectEffect("EffectCarrotBoom");
	//oe->CreateInit(position, direction, scene);
	//oe->GetAniamtor().Play("animations/carrotBoomDeath.csv");
	//oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
	ObjectBullet::OnDie();
}

void BulletCarnationBlueSeed::SetRotation(float value)
{
	ObjectBullet::SetRotation(value);
	sprite.setRotation(value - 180.f);
}

void BulletCarnationBlueSeed::Flip()
{
	if (direction.y != 0.f)
	{
		SetScale({ direction.y / direction.y, 1.f });
	}
}

void BulletCarnationBlueSeed::Frie()
{
	SetSpeed(100);
	animator.Play("animations/carnationVinusMove.csv");
}

sf::RectangleShape BulletCarnationBlueSeed::GetCustomBounds() const
{
	return customBounds;
}
