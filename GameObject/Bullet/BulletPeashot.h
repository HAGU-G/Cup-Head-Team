#pragma once
#include "ObjectBullet.h"

class SceneDev3;

class BulletPeashot : public ObjectBullet
{
protected:
	SceneDev3* sceneDev3;

public:
	BulletPeashot(const std::string& name = "BulletPeashot");
	~BulletPeashot() override = default;
	BulletPeashot(const BulletPeashot&) = delete;
	BulletPeashot(BulletPeashot&&) = delete;
	BulletPeashot& operator=(const BulletPeashot&) = delete;
	BulletPeashot& operator=(BulletPeashot&&) = delete;

	static BulletPeashot* Create(const sf::Vector2f& pos, Direction direction, Scene* scene);
	static BulletPeashot* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Init() override;
	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void OnCreate() override;
	void OnDie() override;
};

