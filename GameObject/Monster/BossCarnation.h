#pragma once
#include "ObjectMonster.h"

class SpriteGo;
class SceneGame;

class BossCarnation : public ObjectMonster
{
	enum class State
	{
		Idle,
		FinalIdle,
		None
	};

protected:
	SceneGame* sceneGame;

	State state = State::None;
	State preState = State::None;

	sf::Vector2f defaultPos;
	sf::Vector2f viewSize;
	sf::Vector2f setDirection;

	int patternCount = 0;
	float patternTimer = 0.f;
	float patternInterval = 2.0f;
	float shootSpeed = 1.0f;
	float finalPollenTimer = 0.f;
	float finalVineTimer = 0.f;
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
	void Creating();
	void CreatingEffect();
	void FireSeedEffect();
	void FireSeed();
	void AddSeed();
	void Intro();
	void Idle();
	void FinalIntro();
	void CreateFinalVine();
	void FirePollen();
	void FinalIdle();
	void FinalFiringPollen();
	void FinalAttackPlayForm();
	void Death();
	void OnDie();

	bool PatternTimer(float dt);
	void SetState(State state);

	State GetState() { return state; }
	sf::RectangleShape GetCustomBounds() const override;
};

