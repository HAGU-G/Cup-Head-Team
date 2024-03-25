#include "pch.h"
#include "BulletCroaksFirefly.h"
#include <SceneGame.h>


void BulletCroaksFirefly::Flip()
{
}

void BulletCroaksFirefly::Homing(float dt)
{
	SetDirection(sf::Transform().rotate(Utils::Angle360(targetPosition - position)).transformPoint(1.f, 0.f), true);
}

BulletCroaksFirefly::BulletCroaksFirefly(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCroaksFirefly* BulletCroaksFirefly::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCroaksFirefly* bcf = new BulletCroaksFirefly();
	bcf->CreateInit(pos, direction, scene);
	bcf->SetRotation(0.f);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcf);
	return bcf;

}

void BulletCroaksFirefly::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();

	HomingTimer += dt;
	if (HomingTimer > HomingInterval && HomingTimer < 2)
	{
		SetSpeed(0.f);
	}
	else if (HomingTimer > 2 && HomingTimer < 2.3f)
	{
		type = Type::Homing;
		SetSpeed(100.f);
		HomingTimer = 0.f;
	}

}

void BulletCroaksFirefly::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	animator.Play("animations/CroaksFireFly.csv");
	SetRange(1200.f);
	SetRotateSpeed(30.f);
	
	int random = rand() % 2;
	
	switch (random)
	{
	case 0:
		SetSpeed(80);
		break;
	case 1:
		SetSpeed(90);
		break;
	default:
		break;
	}
	type = Type::Straight;
	maxHp = 30;
	hp = 30;
}

void BulletCroaksFirefly::OnDie()
{
	ObjectBullet::OnDie();
}
