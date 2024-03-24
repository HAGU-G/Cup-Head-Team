#include "pch.h"
#include "BulletCarrotRing.h"
#include <Effect/ObjectEffect.h>
#include "SceneGame.h"

BulletCarrotRing::BulletCarrotRing(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarrotRing* BulletCarrotRing::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarrotRing* bcr = new BulletCarrotRing();
	bcr->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcr);
	return bcr;
}

void BulletCarrotRing::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	animator.Play("animations/carrotRing.csv");
	SetSpeed(650.f);
	SetRange(1000.f);
	type = Type::Straight;
}

void BulletCarrotRing::OnDie()
{
	ObjectEffect* oe = new ObjectEffect("EffectCarrotRing");
	oe->CreateInit(position, direction, scene);
	oe->GetAniamtor().Play("animations/carrotRingDeath.csv");
	oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
	ObjectBullet::OnDie();
}