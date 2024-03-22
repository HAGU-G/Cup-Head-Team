#pragma once
#include "ObjectBullet.h"
class BulletPotatoShootPink : public ObjectBullet
{
protected:

public:
	BulletPotatoShootPink(const std::string& name = "BulletPotatoShootPink");
	~BulletPotatoShootPink() override = default;
	BulletPotatoShootPink(const BulletPotatoShootPink&) = delete;
	BulletPotatoShootPink(BulletPotatoShootPink&&) = delete;
	BulletPotatoShootPink& operator=(const BulletPotatoShootPink&) = delete;
	BulletPotatoShootPink& operator=(BulletPotatoShootPink&&) = delete;

	static BulletPotatoShootPink* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);
	
	void Update(float dt) override;
	void Init() override;

	void OnCreate() override;
	void OnDie() override;

	sf::FloatRect GetCustomBounds() const override;

};

