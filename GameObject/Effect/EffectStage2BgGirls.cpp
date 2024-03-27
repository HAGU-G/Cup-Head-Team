#include "pch.h"
#include "EffectStage2BgGirls.h"

EffectStage2BgGirls::EffectStage2BgGirls(const std::string& name)
	:ObjectEffect(name)
{

}

EffectStage2BgGirls* EffectStage2BgGirls::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	EffectStage2BgGirls* esb = new EffectStage2BgGirls();
	esb->CreateInit(pos, direction, scene);
	esb->animator.Play("animations/Stage3BgJazzGirls.csv");
	esb->sortLayer = -1;
	return esb;
}
