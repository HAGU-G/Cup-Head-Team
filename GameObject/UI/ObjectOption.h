#pragma once
#include "GameObject.h"

class SpriteGo;
class TextGo;
class ObjectButton;

class ObjectOption : public GameObject
{
protected:
	int textSize = 50;
	ObjectButton* currentButton = nullptr;

	bool isShowOption = false;
	SpriteGo* optionBack = nullptr;
	ObjectButton* optionAudio = nullptr;
	ObjectButton* optionVisual = nullptr;
	ObjectButton* optionEscape = nullptr;

	bool isOptionSelect = false;
	TextGo* audioText = nullptr;
	ObjectButton* audioMaster = nullptr;
	ObjectButton* audioBgm = nullptr;
	ObjectButton* audioSfx = nullptr;
	TextGo* visualText = nullptr;
	ObjectButton* visualBleeding = nullptr;

	ObjectButton* reStart = nullptr;
	ObjectButton* goTitle = nullptr;

public:
	ObjectOption(const std::string& name = "Button");
	~ObjectOption() override = default;
	ObjectOption() = delete;
	ObjectOption(const ObjectOption&) = delete;
	ObjectOption(ObjectOption&&) = delete;
	ObjectOption& operator=(const ObjectOption&) = delete;
	ObjectOption& operator=(ObjectOption&&) = delete;

	void Init() override;
	void Update(float dt) override;
	void Reset() override;
	void Release() override;

	/// <summary>
	/// 버튼 선택
	/// </summary>
	/// <param name="direction">true : 다음 버튼, false: 이전 버튼</param>
	void ButtonSelect(bool direction = true);
	void ButtonPress();

	void ShowOption(bool value = true);
	void ShowOptionAudio(bool value = true);
	void ShowOptionVisual(bool value = true);
};

