#include "pch.h"
#include "BulletOnionTear.h"
#include "SceneGame.h"

BulletOnionTear::BulletOnionTear(const std::string& name)
	:ObjectBullet(name)
{
}

BulletOnionTear* BulletOnionTear::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, bool isPink)
{
	BulletOnionTear* bot = new BulletOnionTear();
	bot->isPink = isPink;
	bot->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bot);
	return bot;
}

void BulletOnionTear::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	if (isPink)
	{
		animator.Play("animations/onionTearPink.csv");
	}
	else
	{
		animator.Play("animations/onionTear.csv");
	}
	SetSpeed(600.f);
	SetRange(1200.f);
	type = Type::Straight;
	ObjectBullet::Init();
}

void BulletOnionTear::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();

}
void BulletOnionTear::OnDie()
{
	ObjectBullet::OnDie();
}

void BulletOnionTear::SetRotation(float value)
{
	ObjectBullet::SetRotation(value - 90.f);
}
