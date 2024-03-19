#pragma once
#include "ObjectBullet.h"
class BulletPeashot : public ObjectBullet
{
protected:

public:
	BulletPeashot(const std::string& name = "BulletPeashot");
	~BulletPeashot() override = default;
	BulletPeashot(const BulletPeashot&) = delete;
	BulletPeashot(BulletPeashot&&) = delete;
	BulletPeashot& operator=(const BulletPeashot&) = delete;
	BulletPeashot& operator=(BulletPeashot&&) = delete;


	void Init() override;

	static BulletPeashot* Create(const sf::Vector2f& pos, Direction direction, Scene* scene);
	static BulletPeashot* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
};

