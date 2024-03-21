#pragma once
#include "SpriteGo.h"


class ObjectBullet : public SpriteGo
{
protected:
	enum class Type
	{
		Straight,
		Homing,
	};
	enum class Owner
	{
		Player,
		Enemy,
	};

	Type type = Type::Straight;
	Owner owner = Owner::Player;

	sf::Vector2f prePosition;
	sf::Vector2f direction;
	sf::Vector2f targetPosition;
	float speed = 0.f;
	float rotateSpeed = 0.f;
	float range = 0.f;
	float moveDistance = 0.f;
	bool doHoming = true;

	sf::RectangleShape bound;

public:
	ObjectBullet(const std::string& name = "Bullet");
	~ObjectBullet() override;
	ObjectBullet(const ObjectBullet&) = delete;
	ObjectBullet(ObjectBullet&&) = delete;
	ObjectBullet& operator=(const ObjectBullet&) = delete;
	ObjectBullet& operator=(ObjectBullet&&) = delete;

	void CreateInit(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Init() override;
	void Release() override;

	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	inline void SetSpeed(float speed) { this->speed = speed; }
	inline void SetRotateSpeed(float rotateSpeed) { this->rotateSpeed = rotateSpeed; }
	inline void SetRange(float range) { this->range = range; }
	void SetDirection(Direction direction);
	void SetDirection(const sf::Vector2f& direction, bool isConversed = false);
	void SetPosition(const sf::Vector2f& position) override;
	void SetTargetPosition(const sf::Vector2f position);

	void Flip();
	void Homing(float dt);

	virtual void OnCreate();
	virtual void OnDie();



};

