#pragma once
#include "Scene.h"
#include "GameObject/Monster/ObjectMonster.h"

class ObjectOption;
class ObjectBullet;

class SceneGame : public Scene
{
public:
	enum class Status
	{
		None = -1,

		Intro,
		FightIntro,
		Fight,
		Victory,
		Defeat,
		Exit,

		Option,
		GoTitle,
		Reset,
	};

protected:
	std::list<ObjectMonster*> monsterList;
	std::vector<SpriteGo*> toeholdList;
	std::deque<ObjectBullet*> enemyBulletList;
	Status status = Status::None;
	float timer = 0.f;
	float timeLimit = 2.f;

	std::string announcerLeft = "resource/Menu/sfx_level_announcer_000";
	std::string announcerRight = ".wav";

	std::string readyLeft = "resource/FightText/FightText_GetReady_";
	std::string victoryLeft = "resource/FightText/FightText_KO_";
	std::string fightTextMiddle;
	std::string fightTextRight = ".png";

	bool pauseWorld = false;
	float parryEffectTimer = 0.0f;
	float parryEffectDuration = 0.35f;
	ObjectOption* option = nullptr;

public:
	bool isParryed = false;

	SceneGame(SceneIds id);
	virtual ~SceneGame();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderTexture& window) override;

	void AddMonster(ObjectMonster* monster);
	const std::list<ObjectMonster*>& GetAllMonsters() const;

	void Addtoehold(SpriteGo* toehold);
	const std::vector<SpriteGo*>& GetAlltoehold() const;

	void AddEnemyBullet(ObjectBullet* enemyBullet);
	const std::deque<ObjectBullet*>& GetAllEnemyBullet() const;

	void SetStatus(Status status);
	inline Status GetStatus() const { return status; }

	inline void Pause() { pauseWorld = true; }
	inline void Play() { pauseWorld = false; }
};

