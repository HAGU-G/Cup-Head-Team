#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;
class ObjectButton;

class SceneTitle : public Scene
{
protected:
	bool titleReady = false;

	ObjectButton* currentButton = nullptr;

	sf::Music bgm;
	sf::Sound hint;
	SpriteGo* bg = nullptr;

	int textSize = 50;
	ObjectButton* start = nullptr;
	ObjectButton* option = nullptr;
	ObjectButton* exit = nullptr;

	bool isShowStageCard = false;
	int stageNum = 1;
	SpriteGo* stageCardBack = nullptr;
	SpriteGo* stageCardGlow = nullptr;
	TextGo* stageCardX = nullptr;
	SpriteGo* stageCardName = nullptr;
	SpriteGo* stageCardTitle = nullptr;
	SpriteGo* stageCardNotReady = nullptr;

	bool isShowOption = false;
	SpriteGo* optionBack = nullptr;
	ObjectButton* optionAudio = nullptr;
	ObjectButton* optionVisual = nullptr;
	ObjectButton* optionEscape = nullptr;

	bool isOptionSelect = false;

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

	/// <summary>
	/// 버튼 선택
	/// </summary>
	/// <param name="direction">true : 다음 버튼, false: 이전 버튼</param>
	void ButtonSelect(bool direction = true);
	void ButtonPress();

	void ShowStageCard(bool value = true);
	void ChangeStageCard();
	void StartGame();

	void ShowOption(bool value = true);
};

