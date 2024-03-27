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
	dynamic_cast<SceneGame*>(scene)->AddEnemyBullet(bcp);
	return bcp;
}

void BulletCarnationFinalPlatForm::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	SetCustomBounds(0.6f, 0.7f, Origins::BC);
	SetScale({ 0.8f,0.8f });
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

void BulletCarnationFinalPlatForm::Init()
{
	ObjectBullet::Init();
	SetSpeed(0.f);
	SetRange(3000.f);
	SetScale({ 0.6f,0.6f });
	animator.Play("animations/carnationFinalVineAttackIdle.csv");
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_level_flower_vinehand_grow_Start.wav");
	animator.AddEvent(animator.GetCurrentCilpId(), 1, std::bind(&BulletCarnationFinalPlatForm::BackVine, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFinalPlatForm::TimerStart, this));
	type = Type::Straight;
	SetTargetPosition({ 0.f, 300.f });
	maxHp = INT_MAX;
	hp = INT_MAX;
	renderStates = sf::RenderStates();
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
	SetScale({ 0.8f,0.8f });
	animator.Play("animations/carnationFinalVineAttack.csv");
	SOUND_MGR.PlaySfx("resource/Sprite/stage02/sfx_level_flower_vinehand_grow_End.wav");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFinalPlatForm::ReturnStart, this));
}

void BulletCarnationFinalPlatForm::ReturnStart()
{
	retrunStart = true;
}

void BulletCarnationFinalPlatForm::ReturnVine()
{
	SetScale({ 0.8f,0.8f });
	animator.Play("animations/carnationFinalVineAttackReturn.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame()-1, std::bind(&BulletCarnationFinalPlatForm::Die, this));
}

void BulletCarnationFinalPlatForm::Die()
{
	SetScale({ 0.8f,0.8f });
	animator.Play("animations/carnationFinalVineAttackIdleReturn.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFinalPlatForm::OnDie, this));
}

sf::RectangleShape BulletCarnationFinalPlatForm::GetCustomBounds() const
{
	return customBounds;
}

void BulletCarnationFinalPlatForm::SetRotation(float value)
{
	ObjectBullet::SetRotation(value + 45.f);
}