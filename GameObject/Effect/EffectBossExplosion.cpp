#include "pch.h"
#include "EffectBossExplosion.h"

EffectBossExplosion::EffectBossExplosion(const std::string& name)
	:ObjectEffect(name)
{
}

EffectBossExplosion* EffectBossExplosion::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	EffectBossExplosion* ebe = new EffectBossExplosion();
	ebe->CreateInit(pos, direction, scene);
	ebe->animator.Play("animations/bossExplosion.csv");
	ebe->animator.AddEvent(ebe->animator.GetCurrentCilpId(), ebe->animator.GetCurrentClip()->GetTotalFrame(), std::bind(&EffectBossExplosion::OnDie, ebe));

	return ebe;
}
