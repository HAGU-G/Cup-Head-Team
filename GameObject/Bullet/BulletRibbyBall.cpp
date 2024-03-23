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
	dynamic_cast<SceneDev3*>(scene)->AddMonster(brb);
	//dynamic_cast<SceneGame*>(scene)->AddMonster(brb);
	return brb;
}

void BulletRibbyBall::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
	//천장, 바닥 과 충돌 처리 충돌시 y축 값 반전
}

void BulletRibbyBall::Init()
{
	ObjectBullet::Init();

	owner = Owner::Enemy;
	SetTexture("resource/Ribbyball1.png");
	SetSpeed(600.f);
	SetRange(1200.f);
	type = Type::Straight;
}

void BulletRibbyBall::OnCreate()
{
}

void BulletRibbyBall::OnDie()
{
	ObjectBullet::OnDie();
}

sf::FloatRect BulletRibbyBall::GetCustomBounds() const
{
	return customBounds;
}
