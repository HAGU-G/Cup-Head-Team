#include "pch.h"
#include "BulletOnionTear.h"
#include "SceneGame.h"
#include "Effect/ObjectEffect.h"

BulletOnionTear::BulletOnionTear(const std::string& name)
	:ObjectBullet(name)
{
}

BulletOnionTear* BulletOnionTear::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, bool isPink)
{
	BulletOnionTear* bot = new BulletOnionTear();
	bot->isPink = isPink;
	bot->CreateInit(pos, direction, scene);
	dynamic_cast<SceneGame*>(scene)->AddEnemyBullet(bot);
	return bot;
}

void BulletOnionTear::Init()
{
	owner = Owner::Enemy;
	ObjectBullet::Init();
	if (isPink)
	{
		animator.Play("animations/onionTearPink.csv");
	}
	else
	{
		animator.Play("animations/onionTear.csv");
	}
	SetCustomBounds(0.6f, 0.6f, Origins::BC);
	SetSpeed(600.f);
	SetRange(1200.f);
	type = Type::Straight;
}

void BulletOnionTear::Update(float dt)
{
	ObjectBullet::Update(dt);
	customBounds.setPosition(position + sf::Vector2f(0.f, -customBounds.getSize().y * 0.25f));

}
void BulletOnionTear::OnDie()
{
	SOUND_MGR.PlaySfx("resource/Sprite/stage01/onion/sfx_level_veggies_Onion_Teardrop_0"
		+ std::to_string(Utils::RandomRange(1, 7)) + ".wav");


	ObjectEffect* oe = new ObjectEffect("EffectOnionTearDeath");
	oe->CreateInit(position, { 1.f, 0.f }, scene);
	if (isPink)
	{
		oe->GetAniamtor().Play("animations/onionTearPinkDeath.csv");
	}
	else
	{

		oe->GetAniamtor().Play("animations/onionTearDeath.csv");
	}
	oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
	ObjectBullet::OnDie();
}

void BulletOnionTear::SetRotation(float value)
{
	ObjectBullet::SetRotation(value - 90.f);
}
