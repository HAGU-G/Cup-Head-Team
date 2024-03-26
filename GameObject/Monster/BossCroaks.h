#pragma once
#include "ObjectMonster.h"

class Player;

class BossCroaks : public ObjectMonster
{
	enum class State
	{
		Idle,
		Pattern1,
		Pattern2,
		Shoot,
		Fan,
		None
	};
protected:

	State state = State::None;
	State preState = State::None;

	float patternTimer = 0.f;
	float patternInterval = 2.f;

	float fanTimer = 0.f;
	float fanInterval = 8.f;
	float fanBackwardSpeed = 50.f;

	int shootCount = 0;
	int fireFlyCount = 0;
	int patternCount = 0;
	Player* player;
public:

	BossCroaks(const std::string& name = "BossCroaks");
	~BossCroaks() override = default;
	BossCroaks(const BossCroaks&) = delete;
	BossCroaks(BossCroaks&&) = delete;
	BossCroaks& operator=(const BossCroaks&) = delete;
	BossCroaks& operator=(BossCroaks&&) = delete;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void Intro();
	void Idle();
	void Fan();
	void FanEnd();
	void Shoot();
	void ShootEnd();
	void Death();
	void OnDie();

	bool ShootTimer(float dt);
	bool PatternTimer(float dt);
	bool FanTimer(float dt);

	void SetState(State state);

	sf::FloatRect GetCustomBounds() const override;

	bool GetFanState() { return state == State::Fan; }
};

