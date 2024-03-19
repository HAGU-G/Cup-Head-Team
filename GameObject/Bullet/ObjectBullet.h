#pragma once
#include "SpriteGo.h"
class ObjectBullet : public SpriteGo
{
protected:
	sf::Vector2f prePosition;
	sf::Vector2f direction;
	float speed = 0.f;
	float range = 100.f;
	float moveDistance = 0.f;

	sf::RectangleShape bound;

public:
	ObjectBullet(const std::string& name = "");
	~ObjectBullet() override = default;
	ObjectBullet(const ObjectBullet&) = delete;
	ObjectBullet(ObjectBullet&&) = delete;
	ObjectBullet& operator=(const ObjectBullet&) = delete;
	ObjectBullet& operator=(ObjectBullet&&) = delete;

	void Init() override;
	void Release() override;

	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;
	static void Create(const sf::Vector2f&, Direction direction, Scene* scene);

	inline void SetSpeed(float speed) { this->speed = speed; }
	void SetDirection(Direction direction);
	void SetPosition(const sf::Vector2f& position) override;
};

