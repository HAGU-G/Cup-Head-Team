#include "pch.h"
#include "EffectOnionTearsOutro.h"

EffectOnionTearsOutro::EffectOnionTearsOutro(const std::string& name)
	:ObjectEffect(name)
{

}

EffectOnionTearsOutro* EffectOnionTearsOutro::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	EffectOnionTearsOutro* eoto = new EffectOnionTearsOutro();

	eoto->animator.SetTarget(&eoto->sprite);
	eoto->animator.Play("animations/onionTearsOutro.csv");
	eoto->animator.AddEvent(eoto->animator.GetCurrentCilpId(), eoto->animator.GetCurrentClip()->GetTotalFrame(), std::bind(&EffectOnionTearsOutro::OnDie, eoto));
	eoto->CreateInit(pos, direction, scene);

	return eoto;
;
}
