#pragma once

class SpriteGo : public GameObject
{
protected:
	sf::RenderStates renderStates;
	sf::Sprite sprite;
	std::string textureId;
	Animator animator;
	sf::Vector2f size;

	bool hasHitBox = false;
	bool useRenderStates = false;

public:
	SpriteGo(const std::string& name = "");

	virtual sf::FloatRect GetLocalBounds() override;
	virtual sf::FloatRect GetGlobalBounds() override;
	virtual sf::Vector2f GetSize() { return size; }

	void SetTexture(const std::string& textureId, bool resetRect = true);

	void SetPosition(const sf::Vector2f& pos) override;
	void Translate(const sf::Vector2f& delta) override;
	void SetRotation(const float r) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetFlipX(bool filp) override;
	void SetFlipY(bool filp) override;
	
	void Update(float dt) override;
	void Reset() override;
	void Draw(sf::RenderTexture& window) override;

};

