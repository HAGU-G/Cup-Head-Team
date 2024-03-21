#include "pch.h"
#include "EffectOnionTears.h"
#include "EffectOnionTearsOutro.h"

EffectOnionTears::EffectOnionTears(const std::string& name)
	:ObjectEffect(name)
{

}

EffectOnionTears* EffectOnionTears::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, float duration)
{
	EffectOnionTears* eot = new EffectOnionTears();

	eot->animator.SetTarget(&eot->sprite);
	eot->animator.Play("animations/onionTearsIntro.csv");
	eot->animator.PlayQueue("animations/onionTearsLoop.csv");
	eot->duration = duration;
	eot->isDieByTime = true;
	//eot->animator.AddEvent(eot->animator.GetCurrentCilpId(), eot->animator.GetCurrentClip()->GetTotalFrame(), std::bind(&EffectOnionTears::OnDie, eot));
	eot->CreateInit(pos, direction, scene);

	return eot;
}

void EffectOnionTears::OnDie()
{
	EffectOnionTearsOutro::Create(position + sf::Vector2f(sprite.getGlobalBounds().width * GetScale().y, -sprite.getGlobalBounds().height), direction, scene);
	ObjectEffect::OnDie();
}
