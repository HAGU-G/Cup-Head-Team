#pragma once
#include "ObjectBullet.h"
class BulletCloud : public ObjectBullet
{
public:
	BulletCloud(const std::string& name = "Cloud");
	~BulletCloud() override = default;
	BulletCloud(const BulletCloud&) = delete;
	BulletCloud(BulletCloud&&) = delete;
	BulletCloud& operator=(const BulletCloud&) = delete;
	BulletCloud& operator=(BulletCloud&&) = delete;


	static BulletCloud* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void LateUpdate(float dt) override;
};

