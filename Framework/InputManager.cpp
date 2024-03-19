#include "pch.h"
#include "InputManager.h"
#include "rapidcsv.h"

std::list<sf::Keyboard::Key> InputManager::keyPressList;
std::list<sf::Keyboard::Key> InputManager::keyDownList;
std::list<sf::Keyboard::Key> InputManager::keyUpList;
std::deque<std::pair<sf::Keyboard::Key, InputManager::KEY_STATE>> InputManager::combo;
float InputManager::comboTimer = 0.f;
float InputManager::comboTimeLimit = 1.f;
bool InputManager::doComboRecord = false;
bool InputManager::isMouseInWindow = false;
float InputManager::wheelDelta = 0;
std::wstring InputManager::inputText;
bool InputManager::doInputText = false;
size_t InputManager::textSize = 12;

void InputManager::KeyEventUpdate(const sf::Event& event)
{

	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (!IsKeyPress(event.key.code))
		{
			keyPressList.push_back(event.key.code);
			keyDownList.push_back(event.key.code);
			if (doComboRecord)
				combo.push_back({ event.key.code, KEY_STATE::DOWN });
		}
		break;
	case sf::Event::KeyReleased:
		keyPressList.remove(event.key.code);
		keyUpList.push_back(event.key.code);
		if (doComboRecord)
			combo.push_back({ event.key.code, KEY_STATE::UP });
		break;
	case sf::Event::MouseButtonPressed:
		if (!IsKeyPress(event.mouseButton.button))
		{
			keyPressList.push_back(MouseKeyConversion(event.mouseButton.button));
			keyDownList.push_back(MouseKeyConversion(event.mouseButton.button));
			if (doComboRecord)
				combo.push_back({ MouseKeyConversion(event.mouseButton.button), KEY_STATE::DOWN });
		}
		break;
	case sf::Event::MouseButtonReleased:
		keyPressList.remove(MouseKeyConversion(event.mouseButton.button));
		keyUpList.push_back(MouseKeyConversion(event.mouseButton.button));
		if (doComboRecord)
			combo.push_back({ MouseKeyConversion(event.mouseButton.button), KEY_STATE::UP });
		break;
	case sf::Event::MouseLeft:
		isMouseInWindow = false;
		break;
	case sf::Event::MouseEntered:
		isMouseInWindow = true;
		break;
	case sf::Event::MouseWheelScrolled:
		wheelDelta = event.mouseWheelScroll.delta;
		break;
	case sf::Event::TextEntered:
		if (doInputText)
		{
			if (event.text.unicode < 0x0020)
			{
				switch (event.text.unicode)
				{
				case 0x0008:
					if (!inputText.empty())
						inputText.pop_back();
					break;
				case 0x000D:
				case 0x001B:
					doInputText = false;
					break;
				}
				break;
			}
			else if (inputText.size() < textSize && event.text.unicode <= 0x007E)
			{
				switch (event.text.unicode)
				{
				case 0x005C: // "\"
				case 0x002F: // "/"
				case 0x003A: // ":"
				case 0x002A: // "*"
				case 0x003F: // "?"
				case 0x0022: // (")
				case 0x003C: // "<"
				case 0x003E: // ">"
				case 0x007C: // "|"
					break;
				default:
					inputText += event.text.unicode;
					break;
				}
			}
		}
		break;
	}
}

void InputManager::KeyUpdate(float timedetla, float timeScale)
{
	keyDownList.clear();
	keyUpList.clear();
	wheelDelta = 0.f;
	if (doComboRecord && (comboTimer += timedetla * timeScale) > comboTimeLimit)
	{
		doComboRecord = false;
	}
}

bool InputManager::IsKeyPress(const sf::Keyboard::Key key)
{
	return find(keyPressList.begin(), keyPressList.end(), key) != keyPressList.end();
}

bool InputManager::IsKeyDown(const sf::Keyboard::Key key)
{
	return find(keyDownList.begin(), keyDownList.end(), key) != keyDownList.end();
}
bool InputManager::IsKeyUp(const sf::Keyboard::Key key)
{
	return find(keyUpList.begin(), keyUpList.end(), key) != keyUpList.end();
}
void InputManager::ClearKeyList()
{
	keyPressList.clear();
	keyDownList.clear();
	keyUpList.clear();
}

sf::Keyboard::Key InputManager::MouseKeyConversion(const sf::Mouse::Button mouse)
{
	return sf::Keyboard::Key(mouse + sf::Keyboard::KeyCount);
}

sf::Mouse::Button InputManager::MouseKeyConversion(const sf::Keyboard::Key key)
{
	return sf::Mouse::Button(key - sf::Keyboard::KeyCount);
}

bool InputManager::IsKeyPress(const sf::Mouse::Button mouse)
{
	return IsKeyPress(MouseKeyConversion(mouse));
}

bool InputManager::IsKeyDown(const sf::Mouse::Button mouse)
{
	return IsKeyDown(MouseKeyConversion(mouse));
}

bool InputManager::IsKeyUp(const sf::Mouse::Button mouse)
{
	return IsKeyUp(MouseKeyConversion(mouse));
}

float InputManager::GetWheelDelta()
{
	return wheelDelta;
}

bool InputManager::IsPerpectCombo(const SFGM_COMBO& combo)
{
	auto c = combo.begin();
	auto input = InputManager::combo.begin();
	while (c != combo.end() && input != InputManager::combo.end())
	{
		if (*c != *input)
			break;
		c++;
		input++;
		if (c == combo.end())
			return true;
	}
	return false;
}
bool InputManager::IsComboSuccess(const SFGM_COMBO& combo)
{
	auto c = combo.begin();
	for (auto& input : InputManager::combo)
	{
		if (c->second == KEY_STATE::UP)
			c++;
		if (c == combo.end())
			return true;
		if (input == *c)
			c++;
		if (c == combo.end())
			return true;
	}
	return false;
}
bool InputManager::IsExllentCombo(const SFGM_COMBO& combo)
{
	auto c = combo.begin();
	for (auto& input : InputManager::combo)
	{
		if (c->second == KEY_STATE::UP)
			c++;
		if (c == combo.end())
			return true;
		if (input.second == KEY_STATE::UP)
			continue;
		if (input == *c)
			c++;
		else
			return false;
		if (c == combo.end())
			return true;
	}
	return false;
}
void InputManager::ComboRecord(float timeLimit)
{
	if (!doComboRecord)
	{
		combo.clear();
		comboTimeLimit = timeLimit;
		comboTimer = 0.f;
		doComboRecord = true;
	}
}
void InputManager::StopComboRecord()
{
	doComboRecord = false;
}
void InputManager::ClearCombo()
{
	combo.clear();
}

void InputManager::SetDoInputText(bool value, size_t textSize)
{
	doInputText = value;
	InputManager::textSize = textSize;
}




