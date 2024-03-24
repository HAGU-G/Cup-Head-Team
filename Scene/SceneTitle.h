#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;
class ObjectButton;

class SceneTitle : public Scene
{
protected:
	bool titleReady = false;

	int selectButton = 1;
	int stageNum = 1;

	sf::Music bgm;
	sf::Sound hint;
	SpriteGo* bg = nullptr;

	ObjectButton* start = nullptr;
	ObjectButton* option = nullptr;
	ObjectButton* exit = nullptr;
	int textSize = 50;

	bool isShowStageCard = false;
	SpriteGo* stageCardBack = nullptr;
	SpriteGo* stageCardGlow = nullptr;
	TextGo* stageCardX = nullptr;
	SpriteGo* stageCardName = nullptr;
	SpriteGo* stageCardTitle = nullptr;
	SpriteGo* stageCardNotReady = nullptr;

public:
	SceneTitle(SceneIds id);
	virtual ~SceneTitle();
	SceneTitle() = default;
	SceneTitle(const SceneTitle&) = delete;
	SceneTitle(SceneTitle&&) = delete;
	SceneTitle& operator=(const SceneTitle&) = delete;
	SceneTitle& operator=(SceneTitle&&) = delete;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Draw(sf::RenderTexture& window) override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void ButtonSelect();
	void ButtonPress();

	void ShowStageCard(bool value = true);
	void ChangeStageCard();
	void StartGame();
};

