#pragma once
#include "ObjectBullet.h"

class BulletCarnationAcon : public ObjectBullet
{
protected:
	float fireTimer = 0.f;

public:
	BulletCarnationAcon(const std::string & name = "BulletCarnationAcon");
	~BulletCarnationAcon() override = default;
	BulletCarnationAcon(const BulletCarnationAcon&) = delete;
	BulletCarnationAcon(BulletCarnationAcon&&) = delete;
	BulletCarnationAcon& operator=(const BulletCarnationAcon&) = delete;
	BulletCarnationAcon& operator=(BulletCarnationAcon&&) = delete;

	static BulletCarnationAcon* Create(const sf::Vector2f & pos, const sf::Vector2f & direction, Scene * scene);

	void Update(float dt) override;
	void Init() override;
	void OnDie() override;

	sf::FloatRect GetCustomBounds() const override;
};

