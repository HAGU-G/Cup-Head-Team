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
	if (i == 1)
	{
		bcp->isPink = true;
	}
	dynamic_cast<SceneGame*>(scene)->AddEnemyBullet(bcp);
	return bcp;
}

void BulletCarnationPollen::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	SetCustomBounds(1.f, 1.f, Origins::MC);
	customBounds.setPosition(position);
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
		hp = 10;
	}
	else if (i == 1)
	{
		animator.Play("animations/carnationFinalFirePollenPink.csv");
		hp = 10;
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

sf::RectangleShape BulletCarnationPollen::GetCustomBounds() const
{
	return customBounds;
}