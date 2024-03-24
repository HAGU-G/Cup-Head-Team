#include "pch.h"
#include "BulletCarnationAcon.h"

BulletCarnationAcon::BulletCarnationAcon(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationAcon* BulletCarnationAcon::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarnationAcon* bca = new BulletCarnationAcon();
	bca->CreateInit(pos, direction, scene);
	return bca;
}

void BulletCarnationAcon::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();

	fireTimer += dt;
	if (fireTimer >= 1.f)
	{
		animator.Play("animations/fireAcon.csv");
		SetScale({ -1.f, abs(direction.x) / direction.x });
		SetSpeed(800.f);
	}
}

void BulletCarnationAcon::Init()
{
	ObjectBullet::Init();
	animator.Play("animations/spinAcon.csv");
	SetSpeed(0.f);
	SetRange(1500.f);
	type = Type::Straight;
	SetTargetPosition({ 0.f, 300.f });
	ObjectBullet::Init();
}

void BulletCarnationAcon::OnDie()
{
	ObjectBullet::OnDie();
}

sf::FloatRect BulletCarnationAcon::GetCustomBounds() const
{
	return customBounds;
}