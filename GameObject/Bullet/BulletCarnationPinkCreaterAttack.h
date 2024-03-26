#pragma once
#include "ObjectBullet.h"

class BulletCarnationPinkCreaterAttack : public ObjectBullet
{
protected:

	float fireTimer = 0.f;
	float fireInterval = 0.f;
public:
	BulletCarnationPinkCreaterAttack(const std::string& name = "BulletCarnationPinkCreaterAttack");
	~BulletCarnationPinkCreaterAttack() override = default;
	BulletCarnationPinkCreaterAttack(const BulletCarnationPinkCreaterAttack&) = delete;
	BulletCarnationPinkCreaterAttack(BulletCarnationPinkCreaterAttack&&) = delete;
	BulletCarnationPinkCreaterAttack& operator=(const BulletCarnationPinkCreaterAttack&) = delete;
	BulletCarnationPinkCreaterAttack& operator=(BulletCarnationPinkCreaterAttack&&) = delete;

	static BulletCarnationPinkCreaterAttack* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;
	void OnDie() override;

	float SetFireInterval(float f) { return fireInterval = f; }
	sf::RectangleShape GetCustomBounds() const override;
};

