#pragma once
#include "ObjectMonster.h"
class BossPotato : public ObjectMonster
{
	enum class State
	{
		Intro,
		Idle,
		Pattern1,
		Shot,
		Death,
		Leave,
		None
	};

protected:
	State state = State::None;
	State preState = State::None;

	int patternCount = 0;
	float patternTimer = 0.f;
	float patternInterval = 1.5f;
	int shotCount = 0;
	float shotTimer = 0.f;
	float shotInterval = 0.5f;

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
	void Death();
	void Leave();

	bool PatternTimer(float dt);
	void SetState(State state);

	bool CollisionCheck() override;
};

