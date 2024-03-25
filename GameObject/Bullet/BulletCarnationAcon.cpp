#include "pch.h"
#include "BulletCarnationAcon.h"
#include "SceneGame.h"

BulletCarnationAcon::BulletCarnationAcon(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationAcon* BulletCarnationAcon::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, float interval)
{
	GameObject* player = scene->FindGo("Player");
	sf::Vector2f playerPos = player->GetPosition();

	BulletCarnationAcon* bca = new BulletCarnationAcon();
	bca->CreateInit(pos, direction, scene);
	bca->SetFireInterval(interval);
	bca->SetDirection(playerPos - bca->GetPosition());
	dynamic_cast<SceneGame*>(scene)->AddMonster(bca);
	return bca;
}

void BulletCarnationAcon::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();

	fireTimer += dt;
	if (fireTimer >= fireInterval)
	{
		SetSpeed(800.f);
		SetScale({ -1.f, abs(direction.x) / direction.x });
		animator.Play("animations/fireAcon.csv");
	}
	SetRotation(Utils::Angle360(direction));
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