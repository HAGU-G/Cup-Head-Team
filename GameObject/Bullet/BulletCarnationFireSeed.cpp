#include "pch.h"
#include "BulletCarnationFireSeed.h"

BulletCarnationFireSeed::BulletCarnationFireSeed(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCarnationFireSeed* BulletCarnationFireSeed::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, int i)
{
	BulletCarnationFireSeed* bcf = new BulletCarnationFireSeed();
	bcf->CreateInit(pos, direction, scene);
	bcf->SetColor(i);
	return bcf;
}

void BulletCarnationFireSeed::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds = sprite.getGlobalBounds();
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
		}
		else if (animator.GetCurrentCilpId() == "animations/carnationSeedPink.csv")
		{
			SetSpeed(0.f);
			animator.Play("animations/carnationSeedPinkGround.csv");
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
	}
	else if (i == 1)
	{
		animator.Play("animations/carnationSeedPink.csv");
	}
	else if( i == 2)
	{

		animator.Play("animations/carnationSeedPurple.csv");
	}
	SetSpeed(400.f);
	SetRange(1000.f);
	SetDirection({ 0.f,1.f });
	type = Type::Straight;
	sprite.setRotation(GetRotation() - 90.f);
	ObjectBullet::Init();
}

void BulletCarnationFireSeed::OnDie()
{
	ObjectBullet::OnDie();
}

sf::FloatRect BulletCarnationFireSeed::GetCustomBounds() const
{
	return customBounds;
}

void BulletCarnationFireSeed::SetRotation(float value)
{
	ObjectBullet::SetRotation(value - 90.f);
}

void BulletCarnationFireSeed::Vine()
{
	animator.Play("animations/carnationSeedVine.csv");
}
