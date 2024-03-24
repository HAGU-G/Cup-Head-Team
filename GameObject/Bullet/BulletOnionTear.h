#pragma once
#include "ObjectBullet.h"
class BulletOnionTear : public ObjectBullet
{
protected:
	

public:
	BulletOnionTear(const std::string& name = "BulletOnionTear");
	~BulletOnionTear() override = default;
	BulletOnionTear(const BulletOnionTear&) = delete;
	BulletOnionTear(BulletOnionTear&&) = delete;
	BulletOnionTear& operator=(const BulletOnionTear&) = delete;
	BulletOnionTear& operator=(BulletOnionTear&&) = delete;

	static BulletOnionTear* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, bool isPink = false);

	void Init() override;
	void Update(float dt) override;
	void OnDie() override;

	void SetRotation(float value) override;
};