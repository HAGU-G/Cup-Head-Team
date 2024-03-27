#include "pch.h"
#include "EffectStage2BgWaiter.h"

EffectStage2BgWaiter::EffectStage2BgWaiter(const std::string& name)
	:ObjectEffect(name)
{

}

EffectStage2BgWaiter* EffectStage2BgWaiter::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	EffectStage2BgWaiter* esw = new EffectStage2BgWaiter();
	esw->CreateInit(pos, direction, scene);
	esw->animator.Play("animations/Stage3bgWaiter.csv");
	esw->sortLayer = -1;
	return esw;
}

void EffectStage2BgWaiter::Update(float dt)
{
	animator.Update(dt);

	viewSize = FRAMEWORK.GetStageViewSize();

	position.x += direction.x * speed * dt;
	SetPosition(position);
	if (position.x > viewSize.x + 50.f && direction.x >= 1)
	{
		direction.x *= -1;
	}
	else if (position.x < -viewSize.x - 50.f && direction.x <= -1)
	{
		direction.x *= -1;
	}

	if (direction.x <= -1)
	{
		SetScale({ 1.f,1.f });
	}
	else if (direction.x >= 1)
	{
		SetScale({ -1.f,1.f });
	}
}
