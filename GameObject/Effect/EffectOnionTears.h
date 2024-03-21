#pragma once
#include "ObjectEffect.h"
class EffectOnionTears : public ObjectEffect
{
protected:
public:
	EffectOnionTears(const std::string& name = "EffectOnionTears");
	~EffectOnionTears() override = default;
	EffectOnionTears(const EffectOnionTears&) = delete;
	EffectOnionTears(EffectOnionTears&&) = delete;
	EffectOnionTears& operator=(const EffectOnionTears&) = delete;
	EffectOnionTears& operator=(EffectOnionTears&&) = delete;

	static EffectOnionTears* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, float duration);

	void OnDie() override;
};

