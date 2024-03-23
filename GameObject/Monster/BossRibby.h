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
		None
	};
protected:

	State state = State::None;
	State preState = State::None;

	float shootTimer = 0.f;
	float shootInterval = 3.0f;
	float patternTimer = 0.f;
	float patternInterval = 2.0f;
	float moveSpeed = 100.f;

	int shootCount = 0;
	int patternCount = 0;

	sf::Vector2f moveLeft = sf::Vector2f(-1, 0);
	sf::Vector2f moveRight = sf::Vector2f(1, 0);
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
	void Ball();
	void ballEnd();
	void Death();
	void OnDie();

	bool ShootTimer(float dt);
	bool PatternTimer(float dt);

	void SetState(State state);

	sf::FloatRect GetCustomBounds() const override;
};

