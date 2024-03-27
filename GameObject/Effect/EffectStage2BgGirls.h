#pragma once
#include "ObjectEffect.h"

class EffectStage2BgGirls :public ObjectEffect
{
protected:
public:
	EffectStage2BgGirls(const std::string& name = "EffectStage2BgGirls");
	~EffectStage2BgGirls() override = default;
	EffectStage2BgGirls(const EffectStage2BgGirls&) = delete;
	EffectStage2BgGirls(EffectStage2BgGirls&&) = delete;
	EffectStage2BgGirls& operator=(const EffectStage2BgGirls&) = delete;
	EffectStage2BgGirls& operator=(EffectStage2BgGirls&&) = delete;

	static EffectStage2BgGirls* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
};

