#include "pch.h"
#include "BulletCarnationFireSeed.h"
#include "BulletCarnationAcon.h"
#include "BulletCarnationPurpleSeed.h"
#include "BulletCarnationBlueSeed.h"
#include "BulletCarnationPinkSeed.h"
#include "SceneGame.h"

BulletCarnationFireSeed::BulletCarnationFireSeed(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationFireSeed* BulletCarnationFireSeed::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, int i)
{
	BulletCarnationFireSeed* bcf = new BulletCarnationFireSeed();
	bcf->SetColor(i);
	bcf->CreateInit(pos, direction, scene);
	bcf->hp = 10;
	dynamic_cast<SceneGame*>(scene)->AddEnemyBullet(bcf);
	return bcf;
}

void BulletCarnationFireSeed::Update(float dt)
{
	owner = Owner::Enemy;
	ObjectBullet::Update(dt);
	customBounds.setPosition(position);
	if (animator.GetCurrentCilpId() == "animations/carnationSeedBlue.csv")
	{
		isPink = false;
	}
	else if (animator.GetCurrentCilpId() == "animations/carnationSeedPurple.csv")
	{
		isPink = false;
	}
	else if (animator.GetCurrentCilpId() == "animations/carnationSeedPink.csv")
	{
		isPink = true;
	}
	if (sprite.getPosition().y >= -10)
	{
		if (animator.GetCurrentCilpId() == "animations/carnationSeedBlue.csv")
		{
			SetSpeed(0.f);
			animator.Play("animations/carnationSeedBlueGround.csv");
			animator.AddEvent(animator.GetCurrentCilpId(),animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFireSeed::Vine,this));
		}
		else if (animator.GetCurrentCilpId() == "animations/carnationSeedPurple.csv")
		{
			SetSpeed(0.f);
			animator.Play("animations/carnationSeedPurpleGround.csv");
			animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFireSeed::PurpleVine, this));
		}
		else if (animator.GetCurrentCilpId() == "animations/carnationSeedPink.csv")
		{
			SetSpeed(0.f);
			isPink = false;
			animator.Play("animations/carnationSeedPinkGround.csv");
			animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFireSeed::PinkVine, this));
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Delete))
	{
		OnDie();
	}
}

void BulletCarnationFireSeed::Init()
{
	ObjectBullet::Init();
	if (i == 0)
	{
		animator.Play("animations/carnationSeedBlue.csv");
		hp = 10;
	}
	else if (i == 1)
	{
		animator.Play("animations/carnationSeedPink.csv");
		hp = 10;
	}
	else if( i == 2)
	{
		animator.Play("animations/carnationSeedPurple.csv");
		hp = 10;
	}
	SetCustomBounds(0.6f, 0.6f, Origins::BC);
	SetSpeed(400.f);
	SetRange(1000.f);
	SetDirection({ 0.f,1.f });
	type = Type::Straight;
	sprite.setRotation(GetRotation() - 90.f);
}

void BulletCarnationFireSeed::OnDie()
{
	isAlive = false;
	ObjectBullet::OnDie();
}

sf::RectangleShape BulletCarnationFireSeed::GetCustomBounds() const
{
	return customBounds;
}

void BulletCarnationFireSeed::SetRotation(float value)
{
	ObjectBullet::SetRotation(value - 90.f);
}

void BulletCarnationFireSeed::Vine()
{
	renderStates = sf::RenderStates();
	animator.Play("animations/carnationSeedVine.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFireSeed::VineReturn, this));
}

void BulletCarnationFireSeed::VineReturn()
{
	renderStates = sf::RenderStates();
	BulletCarnationBlueSeed::Create({ position.x ,position.y - sprite.getGlobalBounds().height }, { 1.f,1.f }, scene);
	animator.Play("animations/carnationSeedVineReturn.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFireSeed::OnDie, this));
}

void BulletCarnationFireSeed::PurpleVine()
{
	renderStates = sf::RenderStates();
	SetCustomBounds(0.1f, 0.5f, Origins::BC);
	animator.Play("animations/carnationFireSeedPurpleVine.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), 4, std::bind(&BulletCarnationFireSeed::CreatePurpleMonster, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFireSeed::OnDie, this));
}

void BulletCarnationFireSeed::CreatePurpleMonster()
{
	BulletCarnationPurpleSeed::Create({ position.x ,position.y }, { 1.f,1.f }, scene);
}

void BulletCarnationFireSeed::PinkVine()
{
	renderStates = sf::RenderStates();
	animator.Play("animations/carnationSeedPinkVine.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame()-3, std::bind(&BulletCarnationFireSeed::CreatePinkMonster, this));
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFireSeed::PinkVineReturn, this));
}

void BulletCarnationFireSeed::PinkVineReturn()
{
	renderStates = sf::RenderStates();
	animator.Play("animations/carnationSeedPinkVineReturn.csv");
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BulletCarnationFireSeed::OnDie, this));
}

void BulletCarnationFireSeed::CreatePinkMonster()
{
	BulletCarnationPinkSeed::Create({ position.x ,position.y - sprite.getGlobalBounds().height + 30 }, { 0.f,-1.f }, scene);
}