#include "pch.h"
#include "EffectCarnationPinkDie.h"

EffectCarnationPinkDie::EffectCarnationPinkDie(const std::string& name)
	:ObjectEffect(name)
{
}

EffectCarnationPinkDie* EffectCarnationPinkDie::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	EffectCarnationPinkDie* ecp = new EffectCarnationPinkDie();
	ecp->CreateInit(pos, direction, scene);
	ecp->animator.Play("animations/carnationPinkCreatureDie.csv");
	ecp->animator.AddEvent(ecp->animator.GetCurrentCilpId(), ecp->animator.GetCurrentClip()->GetTotalFrame(), std::bind(&EffectCarnationPinkDie::OnDie, ecp));

	return ecp;
}
