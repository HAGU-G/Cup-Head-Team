#include "pch.h"
#include "EffectCarnationFireSeed.h"

EffectCarnationFireSeed::EffectCarnationFireSeed(const std::string& name)
	:ObjectEffect(name)
{

}

EffectCarnationFireSeed* EffectCarnationFireSeed::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	EffectCarnationFireSeed* eoto = new EffectCarnationFireSeed();
	EffectCarnationFireSeed* eot = new EffectCarnationFireSeed();

	eoto->animator.SetTarget(&eoto->sprite);
	eoto->animator.Play("animations/carnationFireSeedBlue.csv");
	eoto->animator.AddEvent(eoto->animator.GetCurrentCilpId(), eoto->animator.GetCurrentClip()->GetTotalFrame(), std::bind(&EffectCarnationFireSeed::OnDie, eoto));
	eoto->CreateInit(pos, direction, scene);

	eot->animator.SetTarget(&eot->sprite);
	eot->animator.Play("animations/carnationBossFireSeedEffect.csv");
	eot->animator.AddEvent(eot->animator.GetCurrentCilpId(), eot->animator.GetCurrentClip()->GetTotalFrame(), std::bind(&EffectCarnationFireSeed::OnDie, eot));
	eot->CreateInit(pos, direction, scene);

	return eoto;
}
