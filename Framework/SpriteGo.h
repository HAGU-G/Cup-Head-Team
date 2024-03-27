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
	sf::RectangleShape customBounds;
public:

	bool onPlatForm = false;
	bool onToehold = false;
	SpriteGo(const std::string& name = "");
	~SpriteGo() override = default;

	virtual sf::FloatRect GetLocalBounds() override;
	virtual sf::FloatRect GetGlobalBounds() override;
	virtual sf::Vector2f GetSize() { return size; }
	virtual sf::RectangleShape GetCustomBounds() const;
	virtual sf::FloatRect GetCustomBoundsRect() const;
	void SetTexture(const std::string& textureId, bool resetRect = true);

	void SetPosition(const sf::Vector2f& pos) override;
	void Translate(const sf::Vector2f& delta) override;
	void SetRotation(const float r) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetFlipX(bool filp) override;
	void SetFlipY(bool filp) override;
	void SetAlpha(sf::Uint8 alpha);

	void SetCustomBounds(float ratioX, float ratioY, Origins origin);

	void Update(float dt) override;
	void Reset() override;
	void Draw(sf::RenderTexture& window) override;

	inline void UseRenderStates(bool value) { useRenderStates = value; }
	inline sf::RenderStates& GetRenderStates() { return renderStates; }

};

