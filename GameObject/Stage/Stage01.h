#pragma once
#include "GameObject.h"

class BossPotato;
class BossOnion;
class BossCarrot;
class Player;

class Stage01 : public GameObject
{
protected:
	sf::Music bgm;

	BossPotato* potato = nullptr;
	BossOnion* onion = nullptr;
	BossCarrot* carrot = nullptr;
	Player* player = nullptr;
	int phase = 0;

	int totalMaxHp = 0;
	int potatoHp = 0;
	int onionHp = 0;
	int carrotHp = 0;

	sf::Sprite frontFence;
	sf::Sprite frontFlower;
	sf::Sprite ground;
	sf::Sprite field4;
	sf::Sprite field5;
	sf::Sprite field6;
	sf::Sprite field7;
	sf::Sprite field8;
	sf::Sprite field9;
	sf::Sprite field10;
	sf::Sprite field11;
	sf::Sprite sky;

	sf::Vector2f playerPos;
	sf::Vector2f playerPosCorrection;
	sf::Vector2f viewSize;

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
};

