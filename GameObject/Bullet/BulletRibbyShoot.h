#pragma once
#include "ObjectBullet.h"

class SceneGame;

class BulletRibbyShoot : public ObjectBullet
{
protected:
	SceneGame* sceneGame;

public:
	BulletRibbyShoot(const std::string& name = "BulletRibbyShoot");
	~BulletRibbyShoot() override = default;
	BulletRibbyShoot(const BulletRibbyShoot&) = delete;
	BulletRibbyShoot(BulletRibbyShoot&&) = delete;
	BulletRibbyShoot& operator=(const BulletRibbyShoot&) = delete;
	BulletRibbyShoot& operator=(BulletRibbyShoot&&) = delete;

	static BulletRibbyShoot* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;

	void OnCreate() override;
	void OnDie() override;

	sf::FloatRect GetCustomBounds() const override;

};

