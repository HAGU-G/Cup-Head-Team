#pragma once
#include "ObjectMonster.h"

class BossRibby : public ObjectMonster
{
	enum class State
	{
		Idle,
		Pattern1,
		Pattern2,
		Roll,
		Shoot,
		ball,
		None
	};
protected:

	State state = State::None;
	State preState = State::None;

	float shootTimer = 0.f;
	float shootInterval = 0.5f;
	float patternTimer = 0.f;
	float patternInterval = 2.0f;

	float shootSpeed = 1.0f;
	int shootCount = 0;

	int patternCount = 0;

public:
	BossRibby(const std::string& name = "BossRibby");
	~BossRibby() override = default;
	BossRibby(const BossRibby&) = delete;
	BossRibby(BossRibby&&) = delete;
	BossRibby& operator=(const BossRibby&) = delete;
	BossRibby& operator=(BossRibby&&) = delete;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void Intro();
	void Idle();
	void Roll();
	void Shoot();
	void ShootEnd();
	void ball();
	void ballEnd();
	void Death();
	void OnDie();

	bool ShootTimer(float dt);
	bool PatternTimer(float dt);

	void SetState(State state);

	sf::FloatRect GetCustomBounds() const override;
};

