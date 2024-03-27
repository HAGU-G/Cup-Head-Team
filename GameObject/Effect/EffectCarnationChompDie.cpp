#include "pch.h"
#include "EffectCarnationChompDie.h"

EffectCarnationChompDie::EffectCarnationChompDie(const std::string& name)
	:ObjectEffect(name)
{
}

EffectCarnationChompDie* EffectCarnationChompDie::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	EffectCarnationChompDie* ecc = new EffectCarnationChompDie();
	ecc->CreateInit(pos, direction, scene);
	ecc->animator.Play("animations/carnationChamperDie.csv");
	ecc->animator.AddEvent(ecc->animator.GetCurrentCilpId(), ecc->animator.GetCurrentClip()->GetTotalFrame(), std::bind(&EffectCarnationChompDie::OnDie, ecc));

	return ecc;
}
