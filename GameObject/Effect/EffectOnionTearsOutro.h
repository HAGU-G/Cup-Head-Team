#pragma once
#include "ObjectEffect.h"

class EffectOnionTearsOutro : public ObjectEffect
{
protected:
public:
	EffectOnionTearsOutro(const std::string& name = "EffectOnionTears");
	~EffectOnionTearsOutro() override = default;
	EffectOnionTearsOutro(const EffectOnionTearsOutro&) = delete;
	EffectOnionTearsOutro(EffectOnionTearsOutro&&) = delete;
	EffectOnionTearsOutro& operator=(const EffectOnionTearsOutro&) = delete;
	EffectOnionTearsOutro& operator=(EffectOnionTearsOutro&&) = delete;

	static EffectOnionTearsOutro* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
};

