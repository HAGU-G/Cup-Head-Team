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
		oe->animator.SetTarget(&oe->sprite);
		oe->animator.SetCurrentCilp("animations/peashotCreate.csv");
	}
	else
	{
		oe->animator.SetTarget(&oe->sprite);
		oe->animator.SetCurrentCilp("animations/peashotDeath.csv");
	}
	oe->animator.AddEvent(oe->animator.GetCurrentCilpId(), oe->animator.GetCurrentClip()->GetTotalFrame(), std::bind(&EffectPeashot::OnDie, oe));
	oe->animator.Play();
	oe->CreateInit(pos, direction, scene);

	return oe;
}

