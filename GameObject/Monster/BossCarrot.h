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

	sf::Sprite shootEyes;
	Animator eyeAnimator;

	float patternTimer = 0.f;
	float patternInterval = 3.0f;
	float boomTimer = 0.f;
	float boomInterval = 2.f;
	float ringTimer = 0.f;
	float ringInterval = 5.f;

public:
	BossCarrot(const std::string& name = "BossCarrot");
	~BossCarrot() override = default;
	BossCarrot(const BossCarrot&) = delete;
	BossCarrot(BossCarrot&&) = delete;
	BossCarrot& operator=(const BossCarrot&) = delete;
	BossCarrot& operator=(BossCarrot&&) = delete;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderTexture& window) override;

	void Intro();
	void Pattern1();
	void Ring();
	void Death();
	void OnDie();

	void SetState(State state);

	bool CollisionCheck() override;

	bool PatternTimer(float dt);
	bool BoomTimer(float dt);
	bool Ringimer(float dt);
};
