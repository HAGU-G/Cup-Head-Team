#include "pch.h"
#include "BulletCroaksFirefly.h"
#include "SceneDev3.h"
#include "SceneGame.h"

BulletCroaksFirefly::BulletCroaksFirefly(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCroaksFirefly* BulletCroaksFirefly::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCroaksFirefly* bcf = new BulletCroaksFirefly();
	bcf->CreateInit(pos, direction, scene);
	dynamic_cast<SceneDev3*>(scene)->AddMonster(bcf);
	//dynamic_cast<SceneGame*>(scene)->AddMonster(bcf);
	return bcf;
}

void BulletCroaksFirefly::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
}

void BulletCroaksFirefly::Init()
{
	ObjectBullet::Init();
	owner = Owner::Enemy;
	SetTexture("resource/CroaksFireFly.png");
	SetSpeed(600.f);
	SetRange(1200.f);
	type = Type::Homing;
}

void BulletCroaksFirefly::OnDie()
{
	ObjectBullet::OnDie();
}

sf::FloatRect BulletCroaksFirefly::GetCustomBounds() const
{
	return customBounds;
}
