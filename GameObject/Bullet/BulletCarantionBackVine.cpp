#include "pch.h"
#include "BulletCarantionBackVine.h"
#include "SceneGame.h"

BulletCarantionBackVine::BulletCarantionBackVine(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarantionBackVine* BulletCarantionBackVine::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarantionBackVine* bcb = new BulletCarantionBackVine();
	bcb->CreateInit(pos, direction, scene);
	bcb->sortLayer = -1;
	dynamic_cast<SceneGame*>(scene)->AddEnemyBullet(bcb);
	return bcb;
}

void BulletCarantionBackVine::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	SetCustomBounds(1.f, 1.f, Origins::BC);
	customBounds.setPosition(position);
	if (timer)
	{
		attackTimer += dt;
		if (attackTimer >= 1.f)
		{
			attackTimer = 0;
			Attack();
		}
	}
	if (retrunStart && timer)
	{
		returnTimer += dt;
		if (returnTimer >= 0.5f)
		{
			ReturnVine();
			returnTimer = 0.f;
		}
		timer = false;
		retrunStart = false;
	}
}

void BulletCarantionBackVine::Init()
{
	ObjectBullet::Init();
	animator.Play("animations/carnationFinalVineBack.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarantionBackVine::TimerStart, this));
	SetSpeed(0.f);
	SetRange(3000.f);
	SetScale({ 0.8f,0.8f });
	type = Type::Straight;
	SetTargetPosition({ 0.f, 300.f });
	maxHp = INT_MAX;
	hp = INT_MAX;
	ObjectBullet::Init();
}

void BulletCarantionBackVine::OnDie()
{
	isAlive = false;
	ObjectBullet::OnDie();
}

void BulletCarantionBackVine::TimerStart()
{
	timer = true;
}

void BulletCarantionBackVine::Attack()
{
	animator.Play("animations/carnationFinalVineBackAttack.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarantionBackVine::ReturnStart, this));
}

void BulletCarantionBackVine::ReturnStart()
{
	retrunStart = true;
}

void BulletCarantionBackVine::ReturnVine()
{
	animator.Play("animations/carnationFinalVineBackAttackReturn.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarantionBackVine::Die, this));
}

void BulletCarantionBackVine::Die()
{
	animator.Play("animations/carnationFinalVineBackReturn.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarantionBackVine::OnDie, this));
}

sf::RectangleShape BulletCarantionBackVine::GetCustomBounds() const
{
	return customBounds;
}

void BulletCarantionBackVine::SetRotation(float value)
{
	ObjectBullet::SetRotation(value + 90.f);
}