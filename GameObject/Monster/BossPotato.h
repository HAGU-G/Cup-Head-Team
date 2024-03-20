#pragma once
#include "SpriteGo.h"
class BossPotato : public SpriteGo
{
	enum class State
	{
		None,
		Intro,
		Idle,
		Shot,
		Death,
		Leave
	};

protected:
	State state = State::None;

	float patternTimer = 0.f;
	float patternInterval = 3.f;
	float shotTimer = 0.f;
	float shotInterval = 1.f;

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
	void Idel();
	void Shot();
	void Death();
	void Leave();

	bool PatternTimer(float dt);
	void SetState(State state);
};

