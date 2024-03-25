#include "pch.h"
#include "BulletCarnationFinalVine.h"
#include "SceneGame.h"

BulletCarnationFinalVine::BulletCarnationFinalVine(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationFinalVine* BulletCarnationFinalVine::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarnationFinalVine* bcf = new BulletCarnationFinalVine();
	bcf->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcf);
	return bcf;
}

void BulletCarnationFinalVine::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
}

void BulletCarnationFinalVine::Init()
{
	ObjectBullet::Init();
	animator.Play("animations/carnationFinalVine.csv");
	SetSpeed(0.f);
	SetRange(3000.f);
	type = Type::Straight;
	SetTargetPosition({ 0.f, 300.f });
	ObjectBullet::Init();
}

void BulletCarnationFinalVine::OnDie()
{
	ObjectBullet::OnDie();
}

sf::FloatRect BulletCarnationFinalVine::GetCustomBounds() const
{
	return customBounds;
}