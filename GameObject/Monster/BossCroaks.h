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
	sf::Sound soundFan;

	Player* player;

	State state = State::None;
	State preState = State::None;

	float patternTimer = -4.f;
	float patternInterval = 6.f;

	float fanTimer = 0.f;
	float fanDuration = 8.f;
	float fanBackwardSpeed = 300.f;
	float deltatime;

	int shootCount = 0;
	int fireFlyCount = 0;
	int patternCount = 0;

	sf::Vector2f playerPos;
	sf::Vector2f direction;
public:

	BossCroaks(const std::string& name = "BossCroaks");
	~BossCroaks() override = default;
	BossCroaks(const BossCroaks&) = delete;
	BossCroaks(BossCroaks&&) = delete;
	BossCroaks& operator=(const BossCroaks&) = delete;
	BossCroaks& operator=(BossCroaks&&) = delete;

	void Init() override;
	void Reset() override;
	void Release() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void Intro();
	void Idle();
	void Fan();
	void Shoot();
	void ShootEnd();
	void Death();
	void OnDie();

	bool ShootTimer(float dt);
	bool PatternTimer(float dt);
	bool FanTimer(float dt);

	void SetState(State state);
	sf::RectangleShape GetCustomBounds() const override;

};

