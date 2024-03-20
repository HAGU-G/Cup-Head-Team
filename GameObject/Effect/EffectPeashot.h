#pragma once
#include "ObjectEffect.h"
class EffectPeashot : public ObjectEffect
{
protected:
public:
	EffectPeashot(const std::string& name = "EffectPeashotCreate");
	~EffectPeashot() override = default;
	EffectPeashot(const EffectPeashot&) = delete;
	EffectPeashot(EffectPeashot&&) = delete;
	EffectPeashot& operator=(const EffectPeashot&) = delete;
	EffectPeashot& operator=(EffectPeashot&&) = delete;

	static EffectPeashot* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, bool isCreate);

};

