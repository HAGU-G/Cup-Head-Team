#pragma once
#include "ObjectEffect.h"

class EffectCarnationChompDie : public ObjectEffect
{
protected:
public:
	EffectCarnationChompDie(const std::string& name = "EffectCarnationChompDie");
	~EffectCarnationChompDie() override = default;
	EffectCarnationChompDie(const EffectCarnationChompDie&) = delete;
	EffectCarnationChompDie(EffectCarnationChompDie&&) = delete;
	EffectCarnationChompDie& operator=(const EffectCarnationChompDie&) = delete;
	EffectCarnationChompDie& operator=(EffectCarnationChompDie&&) = delete;


	static EffectCarnationChompDie* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
};
