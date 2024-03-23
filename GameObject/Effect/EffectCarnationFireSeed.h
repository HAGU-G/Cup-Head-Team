#pragma once
#include "ObjectEffect.h"

class EffectCarnationFireSeed : public ObjectEffect
{
protected:
public:
	EffectCarnationFireSeed(const std::string& name = "EffectCarnationFireSeed");
	~EffectCarnationFireSeed() override = default;
	EffectCarnationFireSeed(const EffectCarnationFireSeed&) = delete;
	EffectCarnationFireSeed(EffectCarnationFireSeed&&) = delete;
	EffectCarnationFireSeed& operator=(const EffectCarnationFireSeed&) = delete;
	EffectCarnationFireSeed& operator=(EffectCarnationFireSeed&&) = delete;

	static EffectCarnationFireSeed* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
};

