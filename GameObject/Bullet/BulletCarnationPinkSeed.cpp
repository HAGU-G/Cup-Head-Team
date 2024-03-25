#include "pch.h"
#include "BulletCarnationPinkSeed.h"
#include "SceneGame.h"

BulletCarnationPinkSeed::BulletCarnationPinkSeed(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationPinkSeed* BulletCarnationPinkSeed::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarnationPinkSeed* bcp = new BulletCarnationPinkSeed();
	bcp->CreateInit(pos, direction, scene);
	bcp->isPink = false;
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcp);
	return bcp;
}

void BulletCarnationPinkSeed::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
	if (sprite.getPosition().y <= -500)
	{
		SetDirection({ 1.f,0.f });
		if (sprite.getPosition().x >= 300)
		{
			right = true;
			left = false;
		}
		else if (sprite.getPosition().x <= -500)
		{
			right = false;
			left = true;
		}
		if (right)
		{
			direction.x = -1;
			SetDirection(direction);
		}
		else if (left)
		{
			direction.x = 1;
			SetDirection(direction);
		}
	}
}

void BulletCarnationPinkSeed::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	animator.Play("animations/carnationBossCreatPinkCreater.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationPinkSeed::Move, this));
	SetSpeed(0.f);
	SetRange(15000.f);
	type = Type::Straight;
	SetRotateSpeed(400.f);
	maxHp = 50;
	hp = 50;
}

void BulletCarnationPinkSeed::OnDie()
{
	//ObjectEffect* oe = new ObjectEffect("EffectCarrotBoom");
	//oe->CreateInit(position, direction, scene);
	//oe->GetAniamtor().Play("animations/carrotBoomDeath.csv");
	//oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
	ObjectBullet::OnDie();
}

void BulletCarnationPinkSeed::SetRotation(float value)
{
	//ObjectBullet::SetRotation(value);
	//sprite.setRotation(value - 180.f);
}

void BulletCarnationPinkSeed::Move()
{
	SetSpeed(300);
	animator.Play("animations/carnationBossCreatPinkCreaterMove.csv");
}

void BulletCarnationPinkSeed::Flip()
{
	if (direction.y != 0.f)
	{
		SetScale({ direction.y / direction.y, 1.f });
	}
}

void BulletCarnationPinkSeed::Frie()
{
	SetSpeed(100);
	animator.Play("animations/carnationVinusMove.csv");
}

sf::FloatRect BulletCarnationPinkSeed::GetCustomBounds() const
{
	return customBounds;
}