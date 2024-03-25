#pragma once
#include "GameObject.h"

class TextGo : public GameObject
{
protected:
	sf::Text text;

public:
	TextGo(const std::string& name = "");

	virtual sf::FloatRect GetLocalBounds() override;
	virtual sf::FloatRect GetGlobalBounds() override;

	void SetString(const sf::String& str);
	void Set(const sf::Font& texture, const std::string& str, int size, const sf::Color& color);

	void SetFont(const std::string& textureId);
	void SetFont(const sf::Font& texture);

	void SetOutline(const sf::Color& color, float thick);
	inline void SetCharacterSize(int size) { text.setCharacterSize(size); }

	void SetPosition(const sf::Vector2f& pos) override;
	void Translate(const sf::Vector2f& delta) override;
	void SetRotation(float r) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetFlipX(bool filp) override;
	void SetFlipY(bool filp) override;

	sf::Text& GetText() { return text; }

	void Draw(sf::RenderTexture& window) override;
};

