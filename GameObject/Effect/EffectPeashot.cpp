#include "pch.h"
#include "EffectPeashot.h"

EffectPeashot::EffectPeashot(const std::string& name)
	:ObjectEffect(name)
{

}

EffectPeashot* EffectPeashot::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, bool isCreate)
{
	EffectPeashot* oe = new EffectPeashot();
	if (isCreate)
	{
		oe->SetTexture("resource/Sprite/peashot/weapon_peashot_spark_0004.png");
		oe->SetOrigin(Origins::MC);
	}
	else
	{
		oe->SetTexture("resource/Sprite/peashot/weapon_peashot_death_0001.png");
		oe->SetOrigin(Origins::MC);
	}
	oe->CreateInit(pos, direction, scene);

	oe->isDieByTime = true;
	oe->duration = 0.5f;

	
	return oe;
}

