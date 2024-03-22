#pragma once
#include "ObjectBullet.h"
class BulletCarrotRing : public ObjectBullet
{
protected:

public:
	BulletCarrotRing(const std::string& name = "BulletCarrotRing");
	~BulletCarrotRing() override = default;
	BulletCarrotRing(const BulletCarrotRing&) = delete;
	BulletCarrotRing(BulletCarrotRing&&) = delete;
	BulletCarrotRing& operator=(const BulletCarrotRing&) = delete;
	BulletCarrotRing& operator=(BulletCarrotRing&&) = delete;

	static BulletCarrotRing* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Init() override;

	void OnDie() override;
};

