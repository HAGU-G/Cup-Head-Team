#pragma once
#include "Scene.h"
#include "GameObject/Monster/ObjectMonster.h"

class SceneGame : public Scene
{
protected:
	std::vector<ObjectMonster*> MonsterList;

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

	void Victory();
};

