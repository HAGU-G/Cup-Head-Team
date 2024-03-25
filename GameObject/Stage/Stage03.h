#pragma once

class ObjectMonster;
class BossCarnation;
class Player;
class SpriteGo;
class SceneGame;

class Stage03 : public GameObject
{
protected:
	sf::Music bgm;
	SceneGame* sceneGame;

	BossCarnation* carnation = nullptr;
	Player* player = nullptr;

	int phase = 0;

	int carnationHp = 0;
	int carnationMaxHp = 0;

	SpriteGo* mainBg;
	SpriteGo* skyBg;
	SpriteGo* frontBush;
	SpriteGo* frontBg;
	SpriteGo* cloudBg;
	SpriteGo* frontCloudBg;
	SpriteGo* cloudBg2;
	SpriteGo* frontCloudBg2;

	sf::Vector2f playerPos;
	sf::Vector2f playerPrePos;
	sf::Vector2f playerPosCorrection;
	sf::Vector2f viewSize;


	float cloudSpeed = -50.f;
	float frontCloudSpeed = -40.f;
public:
	Stage03(const std::string& name = "Stage03");
	~Stage03() override = default;
	Stage03(const Stage03&) = delete;
	Stage03(Stage03&&) = delete;
	Stage03& operator=(const Stage03&) = delete;
	Stage03& operator=(Stage03&&) = delete;

	void Init() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Reset() override;
	void Release() override;
	void Draw(sf::RenderTexture& window) override;

};

