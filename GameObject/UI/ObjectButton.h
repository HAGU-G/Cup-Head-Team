#pragma once
#include "TextGo.h"
#include <functional>

class ObjectButton : public TextGo
{
protected:
	sf::RectangleShape background;

	bool isSelected = false;

	sf::Color colorSelect = sf::Color::White;
	sf::Color colorUnSelect = {70, 70, 70, 255};

	std::function<ObjectButton*()> func = nullptr;

	ObjectButton* preButton = nullptr;
	ObjectButton* nextButton = nullptr;

public:
	ObjectButton(const std::string& name = "Button");
	~ObjectButton() override = default;
	ObjectButton() = delete;
	ObjectButton(const ObjectButton&) = delete;
	ObjectButton(ObjectButton&&) = delete;
	ObjectButton& operator=(const ObjectButton&) = delete;
	ObjectButton& operator=(ObjectButton&&) = delete;

	void Init() override;
	void Release() override;

	void Select(bool playSound = true);
	void Press();
	void UnSelect();

	void SetFunction(std::function<ObjectButton*()> funtion);
	inline void SetColorSelect(const sf::Color& color) { colorSelect = color; }
	inline void SetColorUnSelect(const sf::Color& color) { colorUnSelect = color; }

	/// <summary>
	/// 연결된 버튼으로 선택 변경
	/// </summary>
	/// <param name="direction">true: 다음 버튼, false: 이전 버튼</param>
	/// <returns>선택된 버튼</returns>
	ObjectButton* ButtonMove(bool direction = true);
	void SetNextButton(ObjectButton* button, bool link = true);

};

