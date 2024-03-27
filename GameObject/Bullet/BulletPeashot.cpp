#include "pch.h"
#include "BulletPeashot.h"
#include "Effect/EffectPeashot.h"
#include "SceneGame.h"                                                  /////////////////////////////////////

BulletPeashot::BulletPeashot(const std::string& name)
	:ObjectBullet(name)
{
}

void BulletPeashot::Init()
{
	ObjectBullet::Init();
	if (rand() % 2 == 0)
	{
		animator.SetCurrentCilp("animations/peashotIntroA.csv");
	}
	else
	{
		animator.SetCurrentCilp("animations/peashotIntroB.csv");
	}
	animator.Play();
	animator.PlayQueue("animations/peashotMain.csv");
	SetSpeed(1200.f);
	SetRange(3000.f);
	type = Type::Straight;
}

void BulletPeashot::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void BulletPeashot::Update(float dt)
{
	ObjectBullet::Update(dt);


}
void BulletPeashot::LateUpdate(float dt)
{
	ObjectBullet::LateUpdate(dt);
	switch (shootDirection)
	{
	case Direction::Right:
		SetCustomBounds(0.5f, 0.5f, Origins::MR);
		break;
	case Direction::RightUp:
		SetCustomBounds(0.5f, 0.5f, Origins::TR);
		break;
	case Direction::Up:
		SetCustomBounds(0.5f, 0.5f, Origins::TC);
		break;
	case Direction::LeftUp:
		SetCustomBounds(0.5f, 0.5f, Origins::TL);
		break;
	case Direction::Left:
		SetCustomBounds(0.5f, 0.5f, Origins::ML);
		break;
	case Direction::LeftDown:
		SetCustomBounds(0.5f, 0.5f, Origins::BL);
		break;
	case Direction::Down:
		SetCustomBounds(0.5f, 0.5f, Origins::BC);
		break;
	case Direction::RightDown:
		SetCustomBounds(0.5f, 0.5f, Origins::BR);
		break;
	}
	customBounds.setPosition(position);


	for (auto& monster : sceneGame->GetAllMonsters())
	{
		if (monster->IsAlive() && this->customBounds.getGlobalBounds().intersects(monster->GetCustomBoundsRect()))
		{
			monster->OnDamage(4);
			SOUND_MGR.PlaySfx("resource/sfx_player_weapon_peashot_death_001.wav");
			OnDie();
		}
	}
}


void BulletPeashot::OnCreate()
{
	EffectPeashot::Create(position, Utils::RandomOnUnitCircle(), scene, true);
}

void BulletPeashot::OnDie()
{
	EffectPeashot::Create(bound.getPosition(), direction, scene, false);
	ObjectBullet::OnDie();
}


BulletPeashot* BulletPeashot::Create(const sf::Vector2f& pos, Direction direction, Scene* scene)
{
	BulletPeashot* bp = Create(pos, Utils::DirectionConversion(direction), scene);
	bp->shootDirection = direction;
	return bp;
}

BulletPeashot* BulletPeashot::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletPeashot* bp = new BulletPeashot();
	bp->CreateInit(pos, direction, scene);
	bp->SetPosition(pos + direction * (bp->sprite.getLocalBounds().width - bp->GetOrigin().x) * bp->GetScale().x);
	return bp;
}