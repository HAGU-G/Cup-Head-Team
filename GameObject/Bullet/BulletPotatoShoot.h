#pragma once
#include "ObjectBullet.h"
class BulletPotatoShoot : public ObjectBullet
{
protected:

public:
	BulletPotatoShoot(const std::string& name = "BulletPotatoShoot");
	~BulletPotatoShoot() override = default;
	BulletPotatoShoot(const BulletPotatoShoot&) = delete;
	BulletPotatoShoot(BulletPotatoShoot&&) = delete;
	BulletPotatoShoot& operator=(const BulletPotatoShoot&) = delete;
	BulletPotatoShoot& operator=(BulletPotatoShoot&&) = delete;

	static BulletPotatoShoot* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
	
	void Update(float dt) override;
	void Init() override;

	void OnCreate() override;
	void OnDie() override;

	sf::FloatRect GetCustomBounds() const override;

};

