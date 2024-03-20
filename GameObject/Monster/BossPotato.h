#pragma once
#include "ObjectMonster.h"
class BossPotato : public ObjectMonster
{
	enum class State
	{
		Idle,
		Pattern1,
		Shoot,
		None
	};

protected:
	State state = State::None;
	State preState = State::None;

	int patternCount = 0;
	float patternTimer = 0.f;
	float patternInterval = 2.0f;
	float shootSpeed = 1.0f;

public:
	BossPotato(const std::string& name = "BossPotato");
	~BossPotato() override = default;
	BossPotato(const BossPotato&) = delete;
	BossPotato(BossPotato&&) = delete;
	BossPotato& operator=(const BossPotato&) = delete;
	BossPotato& operator=(BossPotato&&) = delete;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	
	void Intro();
	void Idle();
	void Shoot();
	void ShootEnd();
	void Death();
	void Leave();
	void OnDie();

	bool PatternTimer(float dt);
	void SetState(State state);

	bool CollisionCheck() override;
};

