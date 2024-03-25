#pragma once
#include "GameObject.h"


class ObjectMonster;
class BossPotato;
class BossOnion;
class BossCarrot;
class Player;
class SpriteGo;
class SceneGame;

class Stage01 : public GameObject
{
protected:

	SceneGame* sceneGame;

	BossPotato* potato = nullptr;
	BossOnion* onion = nullptr;
	BossCarrot* carrot = nullptr;

	Player* player = nullptr;

	int phase = 0;

	int totalMaxHp = 0;
	int potatoHp = 0;
	int onionHp = 0;
	int carrotHp = 0;

	SpriteGo* frontFence = nullptr;
	SpriteGo* frontFlower = nullptr;
	SpriteGo* ground = nullptr;
	SpriteGo* field4 = nullptr;
	SpriteGo* field5 = nullptr;
	SpriteGo* field6 = nullptr;
	SpriteGo* field7 = nullptr;
	SpriteGo* field8 = nullptr;
	SpriteGo* field9 = nullptr;
	SpriteGo* field10 = nullptr;
	SpriteGo* field11 = nullptr;
	SpriteGo* sky = nullptr;

	std::list<SpriteGo*> backgrounds;

	sf::Vector2f playerPos;
	sf::Vector2f playerPrePos;
	sf::Vector2f playerPosCorrection;
	sf::Vector2f viewSize;

	bool swapping = false;
	float swapTimer = 0.f;
	float swapTime = 5.f;

public:
	Stage01(const std::string& name = "Stage01");
	~Stage01() override = default;
	Stage01(const Stage01&) = delete;
	Stage01(Stage01&&) = delete;
	Stage01& operator=(const Stage01&) = delete;
	Stage01& operator=(Stage01&&) = delete;

	void Init() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Reset() override;
	void Release() override;
	void Draw(sf::RenderTexture& window) override;

	void SetBackground();
};

