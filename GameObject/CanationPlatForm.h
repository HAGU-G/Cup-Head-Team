#pragma once
#include "SpriteGo.h"

class Player;

class CanationPlatForm : public SpriteGo
{
protected:
	Player* player = nullptr;

	sf::Vector2f Pos;
	sf::Vector2f newPos;
	float speed = 100.f;
public:
	CanationPlatForm(const std::string& name = "CanationPlatForm");
	~CanationPlatForm() override = default;
	CanationPlatForm(const CanationPlatForm&) = delete;
	CanationPlatForm(CanationPlatForm&&) = delete;
	CanationPlatForm& operator=(const CanationPlatForm&) = delete;
	CanationPlatForm& operator=(CanationPlatForm&&) = delete;

	static CanationPlatForm* Create(const sf::Vector2f& pos, Scene* scene);

	void Update(float dt) override;
	void Init() override;
	sf::RectangleShape GetCustomBounds() const override;

	void Draw(sf::RenderTexture& window);
};

