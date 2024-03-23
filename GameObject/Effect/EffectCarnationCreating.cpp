#include "pch.h"
#include "EffectCarnationCreating.h"

EffectCarnationCreating::EffectCarnationCreating(const std::string& name)
	:ObjectEffect(name)
{

}

EffectCarnationCreating* EffectCarnationCreating::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	EffectCarnationCreating* eoto = new EffectCarnationCreating();

	eoto->animator.SetTarget(&eoto->sprite);
	eoto->animator.Play("animations/creatingEffect.csv");
	eoto->animator.AddEvent(eoto->animator.GetCurrentCilpId(), eoto->animator.GetCurrentClip()->GetTotalFrame(), std::bind(&EffectCarnationCreating::OnDie, eoto));
	eoto->CreateInit(pos, direction, scene);

	return eoto;
}
