#include "pch.h"
#include "BulletCarnationPollen.h"
#include "SceneGame.h"

BulletCarnationPollen::BulletCarnationPollen(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationPollen* BulletCarnationPollen::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, int i)
{
	BulletCarnationPollen* bcp = new BulletCarnationPollen();
	bcp->SetColor(i);
	bcp->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcp);
	return bcp;
}

void BulletCarnationPollen::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
	fireTimer += dt;
	if (fireTimer >= 0.3f)
	{
		direction.y *= -1;
		SetDirection(direction);
		fireTimer = 0;
	}

}

void BulletCarnationPollen::Init()
{
	ObjectBullet::Init();
	if (i == 0)
	{
		animator.Play("animations/carnationFinalFirePollenWhite.csv");
	}
	else if (i == 1)
	{
		isPink = true;
		animator.Play("animations/carnationFinalFirePollenPink.csv");
	}
	SetSpeed(450.f);
	SetRange(1500.f);
	SetDirection({ -1.f,1.f });
	type = Type::Straight;
	ObjectBullet::Init();
}

void BulletCarnationPollen::OnDie()
{
	isAlive = false;
	ObjectBullet::OnDie();
}

sf::FloatRect BulletCarnationPollen::GetCustomBounds() const
{
	return customBounds;
}