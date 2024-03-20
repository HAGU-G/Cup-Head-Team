#pragma once
#include "SpriteGo.h"
class ObjectEffect : public SpriteGo
{
protected:
	float deadTimer = 0.f;
	float duration = 0.f;
	bool isDieByTime = false;

	Animator animator;
	
	sf::Vector2f direction;

public:
	ObjectEffect(const std::string& name = "Effect");
	~ObjectEffect() override = default;
	ObjectEffect(const ObjectEffect&) = delete;
	ObjectEffect(ObjectEffect&&) = delete;
	ObjectEffect& operator=(const ObjectEffect&) = delete;
	ObjectEffect& operator=(ObjectEffect&&) = delete;

	void CreateInit(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
	static ObjectEffect* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Init() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetDirection(const sf::Vector2f direction);
};

