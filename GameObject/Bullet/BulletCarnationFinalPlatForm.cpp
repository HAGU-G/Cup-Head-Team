#include "pch.h"
#include "BulletCarnationFinalPlatForm.h"
#include "SceneGame.h"
#include "BulletCarantionBackVine.h"

BulletCarnationFinalPlatForm::BulletCarnationFinalPlatForm(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationFinalPlatForm* BulletCarnationFinalPlatForm::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCarnationFinalPlatForm* bcp = new BulletCarnationFinalPlatForm();
	bcp->CreateInit(pos, direction, scene);
	bcp->sortLayer = 2;
	dynamic_cast<SceneGame*>(scene)->AddMonster(bcp);
	return bcp;
}

void BulletCarnationFinalPlatForm::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
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

void BulletCarnationFinalPlatForm::Init()
{
	ObjectBullet::Init();
	animator.Play("animations/carnationFinalVineAttackIdle.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), 1, std::bind(&BulletCarnationFinalPlatForm::BackVine, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFinalPlatForm::TimerStart, this));
	SetSpeed(0.f);
	SetRange(3000.f);
	SetScale({ 0.8f,0.8f });
	type = Type::Straight;
	SetTargetPosition({ 0.f, 300.f });
	ObjectBullet::Init();
}

void BulletCarnationFinalPlatForm::OnDie()
{
	isAlive = false;
	ObjectBullet::OnDie();
}

void BulletCarnationFinalPlatForm::BackVine()
{
	BulletCarantionBackVine::Create(sprite.getPosition(), {0.f,-1.f}, scene);
}

void BulletCarnationFinalPlatForm::TimerStart()
{
	timer = true;
}

void BulletCarnationFinalPlatForm::Attack()
{
	animator.Play("animations/carnationFinalVineAttack.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFinalPlatForm::ReturnStart, this));
}

void BulletCarnationFinalPlatForm::ReturnStart()
{
	retrunStart = true;
}

void BulletCarnationFinalPlatForm::ReturnVine()
{
	animator.Play("animations/carnationFinalVineAttackReturn.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame()-1, std::bind(&BulletCarnationFinalPlatForm::Die, this));
}

void BulletCarnationFinalPlatForm::Die()
{
	animator.Play("animations/carnationFinalVineAttackIdleReturn.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFinalPlatForm::OnDie, this));
}

sf::FloatRect BulletCarnationFinalPlatForm::GetCustomBounds() const
{
	return customBounds;
}

void BulletCarnationFinalPlatForm::SetRotation(float value)
{
	ObjectBullet::SetRotation(value + 90.f);
}