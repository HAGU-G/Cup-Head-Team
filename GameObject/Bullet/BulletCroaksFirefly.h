#pragma once
#include "ObjectBullet.h"

class BulletCroaksFirefly : public ObjectBullet
{
protected:
	float HomingTimer = 0.f;
	float HomingInterval = 1.5f;
	float moveForwardTimer = 1.0f;
	void Flip() override;
	void Homing(float dt) override;	
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

};

