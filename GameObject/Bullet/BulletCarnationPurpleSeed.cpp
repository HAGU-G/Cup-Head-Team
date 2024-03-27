#include "pch.h"
#include "BulletCarnationPurpleSeed.h"
#include "SceneGame.h"
#include "Effect/EffectCarnationChompDie.h"

BulletCarnationPurpleSeed::BulletCarnationPurpleSeed(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationPurpleSeed* BulletCarnationPurpleSeed::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarnationPurpleSeed* bcp = new BulletCarnationPurpleSeed();
	bcp->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcp);
	return bcp;
}

void BulletCarnationPurpleSeed::Update(float dt)
{
	ObjectBullet::Update(dt);
	SetCustomBounds(0.6f, 0.5f, Origins::BC);
	customBounds.setPosition({ position.x,position.y + 10.f });
	if (hp <= 0)
	{
		EffectCarnationChompDie::Create({ sprite.getPosition()}, {1.f,0.f}, scene);
		OnDie();
	}
}

void BulletCarnationPurpleSeed::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	animator.Play("animations/carnationSeedPurpleCreater.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), 2, std::bind(&BulletCarnationPurpleSeed::PlaySfx, this));
	SetSpeed(0.f);
	SetRange(100.f);
	type = Type::Straight;
	maxHp = 16;
	hp = 16;
	ObjectBullet::Init();
}

void BulletCarnationPurpleSeed::SetRotation(float value)
{
	ObjectBullet::SetRotation(value - 45.f);
}

void BulletCarnationPurpleSeed::OnDie()
{
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_mermaid_turtle_shell_pop.wav");
	isAlive = false;
	ObjectBullet::OnDie();
}

void BulletCarnationPurpleSeed::PlaySfx()
{
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_flower_venus_a_chomp.wav");
}

sf::RectangleShape BulletCarnationPurpleSeed::GetCustomBounds() const
{
	return customBounds;
}
