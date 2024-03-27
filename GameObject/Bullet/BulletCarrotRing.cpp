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
	dynamic_cast<SceneGame*>(scene)->AddEnemyBullet(bcr);
	return bcr;
}

void BulletCarrotRing::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	SOUND_MGR.PlaySfx("resource/Sprite/stage01/carrot/sfx_level_veggies_Carrot_MindMeld_BeamFire_0"
		+ std::to_string(Utils::RandomRange(1, 3)) + ".wav");
	animator.Play("animations/carrotRing.csv");
	SetSpeed(650.f);
	SetRange(1000.f);
	type = Type::Straight;
}

void BulletCarrotRing::Update(float dt)
{
	ObjectBullet::Update(dt);
	SetCustomBounds(0.7f, 0.7f, Origins::MC);
	customBounds.setPosition(position);
}

void BulletCarrotRing::OnDie()
{
	ObjectEffect* oe = new ObjectEffect("EffectCarrotRing");
	oe->CreateInit(position, direction, scene);
	oe->GetAniamtor().Play("animations/carrotRingDeath.csv");
	oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
	ObjectBullet::OnDie();
}