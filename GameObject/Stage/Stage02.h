#pragma once
#include "GameObject.h"

class ObjectMonster;
class BossCroaks;
class BossRibby;
class Player;
class SpriteGo;
class SceneGame;

class Stage02 : public GameObject
{
protected:
	SceneGame* sceneGame;

	BossCroaks* croaks;
	BossRibby* ribby;
	Player* player;

	SpriteGo* bg1;
	SpriteGo* bg2;
	SpriteGo* bg3;
	SpriteGo* bg4;
	SpriteGo* bg5;
	SpriteGo* bg6;

	bool isVictory = false;

	std::list<SpriteGo*> backgrounds;

	sf::Vector2f viewSize;
public:
	Stage02(const std::string& name = "Stage02");
	~Stage02() override = default;
	Stage02(const Stage02&) = delete;
	Stage02(Stage02&&) = delete;
	Stage02& operator=(const Stage02&) = delete;
	Stage02& operator=(Stage02&&) = delete;

	void Init() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Reset() override;
	void Release() override;
	void Draw(sf::RenderTexture& window) override;

	void SetBackground();
};

