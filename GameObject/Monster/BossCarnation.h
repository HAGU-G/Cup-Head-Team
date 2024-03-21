#pragma once
#include "ObjectMonster.h"
class BossCarnation : public ObjectMonster
{
	enum class State
	{
		Idle,
		FinalIdle,
		None
	};

protected:
	State state = State::None;
	State preState = State::None;

	int patternCount = 0;
	float patternTimer = 0.f;
	float patternInterval = 2.0f;
	float shootSpeed = 1.0f;
	int shootCount = 0;

public:
	BossCarnation(const std::string& name = "BossCarnation");
	~BossCarnation() override = default;
	BossCarnation(const BossCarnation&) = delete;
	BossCarnation(BossCarnation&&) = delete;
	BossCarnation& operator=(const BossCarnation&) = delete;
	BossCarnation& operator=(BossCarnation&&) = delete;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void FaHigh();
	void FaLow();
	void Intro();
	void Idle();
	void FinalIntro();
	void FinalIdle();
	void Death();
	void OnDie();

	bool PatternTimer(float dt);
	void SetState(State state);

	bool CollisionCheck() override;
};

