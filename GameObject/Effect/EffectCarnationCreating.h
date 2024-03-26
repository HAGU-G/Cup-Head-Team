#pragma once
#include "ObjectEffect.h"
class EffectCarnationCreating : public ObjectEffect
{
protected:
public:
	EffectCarnationCreating(const std::string& name = "EffectCarnationCreating");
	~EffectCarnationCreating() override = default;
	EffectCarnationCreating(const EffectCarnationCreating&) = delete;
	EffectCarnationCreating(EffectCarnationCreating&&) = delete;
	EffectCarnationCreating& operator=(const EffectCarnationCreating&) = delete;
	EffectCarnationCreating& operator=(EffectCarnationCreating&&) = delete;

	static EffectCarnationCreating* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
};

