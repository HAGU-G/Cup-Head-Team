#pragma once
#include "ObjectMonster.h"
class BossOnion : public ObjectMonster
{
	enum class State
	{
		Idle,
		Pattern1,
		Crying,
		None
	};

protected:
	sf::FloatRect customBounds;//////////////////////////////////

	State state = State::None;
	State preState = State::None;

	int patternCount = 0;
	float patternTimer = 0.f;
	float patternInterval = 2.0f;
	float shootSpeed = 1.0f;
	int shootCount = 0;
public:
	BossOnion(const std::string& name = "BossOnion");
	~BossOnion() override = default;
	BossOnion(const BossOnion&) = delete;
	BossOnion(BossOnion&&) = delete;
	BossOnion& operator=(const BossOnion&) = delete;
	BossOnion& operator=(BossOnion&&) = delete;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void Intro();
	void Idle();
	void Cry();
	void Tears();
	void Death();
	void Leave();
	void OnDie();

	bool PatternTimer(float dt);
	void SetState(State state);

	bool CollisionCheck() override;

	sf::FloatRect GetCustomBounds() const override;
};

