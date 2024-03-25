#pragma once
#include "TextGo.h"
#include <functional>

class ObjectButton : public TextGo
{
protected:
	sf::RectangleShape background;

	bool isSelected = false;

	sf::Color colorSelect = sf::Color::White;
	sf::Color colorUnSelect = {100, 100, 100, 255};

	std::function<ObjectButton*()> func = nullptr;

public:
	ObjectButton(const std::string& name = "Button");
	~ObjectButton() override = default;
	ObjectButton() = delete;
	ObjectButton(const ObjectButton&) = delete;
	ObjectButton(ObjectButton&&) = delete;
	ObjectButton& operator=(const ObjectButton&) = delete;
	ObjectButton& operator=(ObjectButton&&) = delete;

	void Init() override;

	void Select();
	void Press();
	void UnSelect();

	void SetFunction(std::function<ObjectButton*()> funtion);
};

