#include "pch.h"
#include "BulletCarrotBoom.h"
#include "Effect/ObjectEffect.h"
#include <SceneGame.h>

BulletCarrotBoom::BulletCarrotBoom(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarrotBoom* BulletCarrotBoom::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarrotBoom* bcb = new BulletCarrotBoom();
	bcb->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcb);
	return bcb;
}

void BulletCarrotBoom::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
}

void BulletCarrotBoom::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	animator.Play("animations/carrotBoom.csv");
	SetSpeed(150.f);
	SetRange(1500.f);
	type = Type::Homing;
	SetRotateSpeed(180.f);
	maxHp = 30;
	hp = 30;
}

void BulletCarrotBoom::OnDie()
{
	ObjectEffect* oe = new ObjectEffect("EffectCarrotBoom");
	oe->CreateInit(position, direction, scene);
	oe->GetAniamtor().Play("animations/carrotBoomDeath.csv");
	oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
	ObjectBullet::OnDie();
}

void BulletCarrotBoom::SetRotation(float value)
{
	ObjectBullet::SetRotation(value);
	sprite.setRotation(value - 90.f);
}

sf::FloatRect BulletCarrotBoom::GetCustomBounds() const
{
	return customBounds;
}

void BulletCarrotBoom::Flip()
{
	if (direction.y != 0.f)
	{
		SetScale({ abs(direction.y) / direction.y,1.f  });
	}
}