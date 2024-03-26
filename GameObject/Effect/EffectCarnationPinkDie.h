#pragma once
#include "ObjectEffect.h"

class EffectCarnationPinkDie : public ObjectEffect
{
protected:
public:
	EffectCarnationPinkDie(const std::string& name = "EffectCarnationPinkDie");
	~EffectCarnationPinkDie() override = default;
	EffectCarnationPinkDie(const EffectCarnationPinkDie&) = delete;
	EffectCarnationPinkDie(EffectCarnationPinkDie&&) = delete;
	EffectCarnationPinkDie& operator=(const EffectCarnationPinkDie&) = delete;
	EffectCarnationPinkDie& operator=(EffectCarnationPinkDie&&) = delete;


	static EffectCarnationPinkDie* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
};

