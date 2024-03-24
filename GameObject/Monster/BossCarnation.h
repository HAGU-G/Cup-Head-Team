#pragma once
#include "ObjectMonster.h"

class SpriteGo;

class BossCarnation : public ObjectMonster
{
	enum class State
	{
		Idle,
		FinalIdle,
		None
	};

protected:
	sf::FloatRect customBounds;//////////////////////////////////
	State state = State::None;
	State preState = State::None;

	SpriteGo* mainBg;
	SpriteGo* skyBg;
	SpriteGo* frontBush;
	SpriteGo* frontBg;
	SpriteGo* cloudBg;
	SpriteGo* frontCloudBg;
	SpriteGo* cloudBg2;
	SpriteGo* frontCloudBg2;

	sf::Vector2f defaultPos;

	float cloudSpeed = -50.f;
	float frontCloudSpeed = -40.f;
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
	void Draw(sf::RenderTexture& window) override;

	void FaHigh();
	void FaLow();
	void Creating();
	void CreatingEffect();
	void FireSeedEffect();
	void FireSeed();
	void AddSeed();
	void Intro();
	void Idle();
	void FinalIntro();
	void FinalIdle();
	void FinalFiringPollen();
	void Death();
	void OnDie();

	bool PatternTimer(float dt);
	void SetState(State state);

	sf::FloatRect GetCustomBounds() const override;
};

