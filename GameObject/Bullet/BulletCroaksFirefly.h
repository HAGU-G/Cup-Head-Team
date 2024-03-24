#pragma once
#include "ObjectBullet.h"
class BulletCroaksFirefly : public ObjectBullet
{
protected:

public:
	BulletCroaksFirefly(const std::string& name = "BulletCroaksFirefly");
	~BulletCroaksFirefly() override = default;
	BulletCroaksFirefly(const BulletCroaksFirefly&) = delete;
	BulletCroaksFirefly(BulletCroaksFirefly&&) = delete;
	BulletCroaksFirefly& operator=(const BulletCroaksFirefly&) = delete;
	BulletCroaksFirefly& operator=(BulletCroaksFirefly&&) = delete;

	static BulletCroaksFirefly* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;

	void OnDie() override;

	sf::FloatRect GetCustomBounds() const override;
};

