#pragma once
#include "ObjectEffect.h"
class EffectBossExplosion : public ObjectEffect
{
protected:
public:
	EffectBossExplosion(const std::string& name = "EffectBossExplosion");
	~EffectBossExplosion() override = default;
	EffectBossExplosion(const EffectBossExplosion&) = delete;
	EffectBossExplosion(EffectBossExplosion&&) = delete;
	EffectBossExplosion& operator=(const EffectBossExplosion&) = delete;
	EffectBossExplosion& operator=(EffectBossExplosion&&) = delete;


	static EffectBossExplosion* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
};

