#pragma once
#include "ObjectEffect.h"
class EffectStage2BgWaiter : public ObjectEffect
{
protected:
	float speed = 200.f;
	sf::Vector2f viewSize;
public:
	EffectStage2BgWaiter(const std::string& name = "EffectStage2BgWaiter");
	~EffectStage2BgWaiter() override = default;
	EffectStage2BgWaiter(const EffectStage2BgWaiter&) = delete;
	EffectStage2BgWaiter(EffectStage2BgWaiter&&) = delete;
	EffectStage2BgWaiter& operator=(const EffectStage2BgWaiter&) = delete;
	EffectStage2BgWaiter& operator=(EffectStage2BgWaiter&&) = delete;

	static EffectStage2BgWaiter* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
	void Update(float dt) override;
};

