#pragma once
#include "Scene.h"
#include "GameObject/Monster/ObjectMonster.h"

class SpriteGo;

class SceneDev3 : public Scene
{
protected:
	std::vector<ObjectMonster*> BossList;

	SpriteGo* bg1;
	SpriteGo* bg2;
	SpriteGo* bg3;
	SpriteGo* bg4;
	SpriteGo* bg5;

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

