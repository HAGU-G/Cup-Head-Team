#pragma once
#include "ObjectBullet.h"

class BulletCarnationBoomerang : public ObjectBullet
{
protected:
	float fireTimer = 0.f;

public:
	BulletCarnationBoomerang(const std::string& name = "BulletCarnationBoomerang");
	~BulletCarnationBoomerang() override = default;
	BulletCarnationBoomerang(const BulletCarnationBoomerang&) = delete;
	BulletCarnationBoomerang(BulletCarnationBoomerang&&) = delete;
	BulletCarnationBoomerang& operator=(const BulletCarnationBoomerang&) = delete;
	BulletCarnationBoomerang& operator=(BulletCarnationBoomerang&&) = delete;

	static BulletCarnationBoomerang* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;
	void OnDie() override;

	sf::FloatRect GetCustomBounds() const override;
};

