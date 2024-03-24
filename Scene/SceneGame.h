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
};

