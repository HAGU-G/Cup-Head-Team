#pragma once
#include "ObjectMonster.h"
class BossCarrot : public ObjectMonster
{
	enum class State
	{
		Pattern1,
		Pattern2,
		Ring,
		None
	};

protected:
	State state = State::None;
	State preState = State::None;

	sf::Sound soundMindMeld;

	sf::Sprite shootEyes;
	Animator eyeAnimator;
	sf::Vector2f ringCreatePos = { 0.f, 0.f };
	sf::Vector2f targetDirection = { 0.f, 1.f };
	float patternTimer = 0.f;
	float patternInterval = 13.0f;
	float boomTimer = 0.f;
	float boomInterval = 2.5f;
	float ringTimer = 5.f;
	float ringInterval = 2.3f;
	int ringCount = 0;

public:
	BossCarrot(const std::string& name = "BossCarrot");
	~BossCarrot() override;
	BossCarrot(const BossCarrot&) = delete;
	BossCarrot(BossCarrot&&) = delete;
	BossCarrot& operator=(const BossCarrot&) = delete;
	BossCarrot& operator=(BossCarrot&&) = delete;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Release() override;
	void Draw(sf::RenderTexture& window) override;

	void Intro();
	void Pattern1();
	void Ring();
	void ShootRing();
	void SetTargetDirection();
	void Death();
	void OnDie();

	void SetState(State state);

	bool PatternTimer(float dt);
	bool BoomTimer(float dt);
	bool RingTimer(float dt);

	sf::RectangleShape GetCustomBounds() const override;
};

