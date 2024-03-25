#pragma once
#include "Scene.h"
#include "GameObject/Monster/ObjectMonster.h"

class SceneGame : public Scene
{
public:
	enum class Status
	{
		None = -1,
		Intro,
		Fight,
		Victory,
		Defeat,
		Exit,
	};

protected:
	std::vector<ObjectMonster*> MonsterList;

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


public:

	SceneGame(SceneIds id);
	virtual ~SceneGame();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderTexture& window) override;
	void AddMonster(ObjectMonster* monster);
	std::vector<ObjectMonster*> getAllMonsters() const;

	void SetStatus(Status status);
	inline Status GetStatus() const { return status; }

	inline void Pause() { pauseWorld = true; }
	inline void Play() { pauseWorld = false; }
};

