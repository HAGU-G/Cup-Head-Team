#include "pch.h"
#include "BulletRibbyBall.h"
#include "SceneDev3.h"
#include "SceneGame.h"

BulletRibbyBall::BulletRibbyBall(const std::string& name)
	:ObjectBullet(name)
{
}

BulletRibbyBall* BulletRibbyBall::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletRibbyBall* brb = new BulletRibbyBall();
	brb->CreateInit(pos, direction, scene);
	//dynamic_cast<SceneDev3*>(scene)->AddMonster(brb);
	dynamic_cast<SceneGame*>(scene)->AddEnemyBullet(brb);
	return brb;
}

void BulletRibbyBall::Update(float dt)
{
	ObjectBullet::Update(dt);
	float upperBound = -600.0f; 
	float lowerBound = -20.f;
	if (position.y <= upperBound || position.y >= lowerBound)
	{
		direction.y = -direction.y; 
		SetDirection(direction, true); 
	}

	auto bounds = sprite.getGlobalBounds();
	float shrinkFactor = 0.4f;
	float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
	float heightReduction = bounds.height * (1 - shrinkFactor) / 2;
	//customBounds = sf::FloatRect(bounds.left + widthReduction, bounds.top, bounds.width * shrinkFactor, bounds.height);
	SetCustomBounds(shrinkFactor, shrinkFactor, Origins::TL);
	customBounds.setPosition(bounds.left + widthReduction, bounds.top + heightReduction);

}

void BulletRibbyBall::Init()
{
	ObjectBullet::Init();

	owner = Owner::Enemy;
	SetTexture("resource/Ribbyball1.png");
	SetOrigin(Origins::MC);
	SetSpeed(600.f);
	SetRange(3000.f);
	type = Type::Straight;
}

void BulletRibbyBall::OnCreate()
{
}

void BulletRibbyBall::OnDie()
{
	ObjectBullet::OnDie();
}

sf::RectangleShape BulletRibbyBall::GetCustomBounds() const
{
	return customBounds;
}
