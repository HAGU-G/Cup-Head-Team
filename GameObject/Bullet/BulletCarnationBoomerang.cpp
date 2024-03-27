#include "pch.h"
#include "BulletCarnationBoomerang.h"
#include "SceneGame.h"

BulletCarnationBoomerang::BulletCarnationBoomerang(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationBoomerang* BulletCarnationBoomerang::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarnationBoomerang* bcb = new BulletCarnationBoomerang();
	bcb->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcb);
	return bcb;
}

void BulletCarnationBoomerang::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	SetCustomBounds(0.9f, 0.8f, Origins::MC);
	customBounds.setPosition(position);
	if (sprite.getPosition().x <= -800)
	{
		SetPosition({ sprite.getPosition().x,-100.f });
		SetDirection({ 1.f,0.f });
	}
	else if (sprite.getPosition().x >= 700.f)
	{
		OnDie();
	}

	fireTimer += dt;
	if (fireTimer >= 1.f)
	{
		SetSpeed(800.f);
	}

}

void BulletCarnationBoomerang::Init()
{
	ObjectBullet::Init();
	animator.Play("animations/boomerang.csv");
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_boomerang_projectile.wav", true);
	SetSpeed(0.f);
	SetRange(2500.f);
	type = Type::Straight;
	SetTargetPosition({ 0.f, 300.f });
	maxHp = INT_MAX;
	hp = INT_MAX;
	ObjectBullet::Init();
}

void BulletCarnationBoomerang::OnDie()
{
	SOUND_MGR.StopAll();
	isAlive = false;
	ObjectBullet::OnDie();
}

sf::RectangleShape BulletCarnationBoomerang::GetCustomBounds() const
{
	return customBounds;
}