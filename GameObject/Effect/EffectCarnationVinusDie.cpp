#include "pch.h"
#include "EffectCarnationVinusDie.h"

EffectCarnationVinusDie::EffectCarnationVinusDie(const std::string& name)
	:ObjectEffect(name)
{
}

EffectCarnationVinusDie* EffectCarnationVinusDie::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	EffectCarnationVinusDie* ecv = new EffectCarnationVinusDie();
	ecv->CreateInit(pos, direction, scene);
	ecv->animator.Play("animations/carnationVinusDie.csv");
	ecv->animator.AddEvent(ecv->animator.GetCurrentCilpId(), ecv->animator.GetCurrentClip()->GetTotalFrame(), std::bind(&EffectCarnationVinusDie::OnDie, ecv));

	return ecv;
}
