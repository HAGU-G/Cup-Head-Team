#pragma once
#include "ObjectEffect.h"

class EffectCarnationVinusDie : public ObjectEffect
{
protected:
public:
	EffectCarnationVinusDie(const std::string& name = "EffectCarnationVinusDie");
	~EffectCarnationVinusDie() override = default;
	EffectCarnationVinusDie(const EffectCarnationVinusDie&) = delete;
	EffectCarnationVinusDie(EffectCarnationVinusDie&&) = delete;
	EffectCarnationVinusDie& operator=(const EffectCarnationVinusDie&) = delete;
	EffectCarnationVinusDie& operator=(EffectCarnationVinusDie&&) = delete;


	static EffectCarnationVinusDie* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
};
