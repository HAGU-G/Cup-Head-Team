#pragma once
#include "ObjectBullet.h"
class BulletRibbyBall : public ObjectBullet
{
protected:

public:

	BulletRibbyBall(const std::string& name = "BulletRibbyBall");
	~BulletRibbyBall() override = default;
	BulletRibbyBall(const BulletRibbyBall&) = delete;
	BulletRibbyBall(BulletRibbyBall&&) = delete;
	BulletRibbyBall& operator=(const BulletRibbyBall&) = delete;
	BulletRibbyBall& operator=(BulletRibbyBall&&) = delete;

	static BulletRibbyBall* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;

	void OnCreate() override;
	void OnDie() override;

	sf::FloatRect GetCustomBounds() const override;
};

