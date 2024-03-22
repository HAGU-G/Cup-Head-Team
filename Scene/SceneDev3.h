#pragma once
#include "Scene.h"
#include "GameObject/Monster/ObjectMonster.h"

class SceneDev3 : public Scene
{
protected:
	std::vector<ObjectMonster*> BossList;

public:

	SceneDev3(SceneIds id);
	virtual ~SceneDev3();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderTexture& window) override;
	void AddMonster(ObjectMonster* monster);
	std::vector<ObjectMonster*> getAllMonsters() const;
};

