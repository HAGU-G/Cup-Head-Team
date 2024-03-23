#pragma once
#include "Scene.h"

class SpriteGo;
class Player;

class SceneDev2 : public Scene
{
protected:
	sf::CircleShape circle;
	SpriteGo* background = nullptr;
	Player* player = nullptr;
public:
	SceneDev2(SceneIds id);
	virtual ~SceneDev2();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderTexture& window) override;
};

