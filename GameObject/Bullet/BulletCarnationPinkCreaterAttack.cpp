#include "pch.h"
#include "BulletCarnationPinkCreaterAttack.h"
#include "SceneGame.h"

BulletCarnationPinkCreaterAttack::BulletCarnationPinkCreaterAttack(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationPinkCreaterAttack* BulletCarnationPinkCreaterAttack::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	GameObject* player = scene->FindGo("Player");
	sf::Vector2f playerPos = player->GetPosition();

	BulletCarnationPinkCreaterAttack* bpa = new BulletCarnationPinkCreaterAttack();
	bpa->isPink = true;
	bpa->CreateInit(pos, direction, scene);
	bpa->SetDirection(playerPos - bpa->GetPosition());
	dynamic_cast<SceneGame*>(scene)->AddMonster(bpa);
	return bpa;
}

void BulletCarnationPinkCreaterAttack::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();

	SetScale({ -1.f, abs(direction.x) / direction.x });
}

void BulletCarnationPinkCreaterAttack::Init()
{
	ObjectBullet::Init();
	animator.Play("animations/carnationPinkCreatBullet.csv");
	SetSpeed(600.f);
	SetRange(1000.f);
	type = Type::Straight;
	SetTargetPosition({ 0.f, 300.f });
	ObjectBullet::Init();
}

void BulletCarnationPinkCreaterAttack::OnDie()
{
	ObjectBullet::OnDie();
}

sf::FloatRect BulletCarnationPinkCreaterAttack::GetCustomBounds() const
{
	return customBounds;
}