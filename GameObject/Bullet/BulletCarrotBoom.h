#pragma once
#include "ObjectBullet.h"
class BulletCarrotBoom : public ObjectBullet
{
protected:

public:
	BulletCarrotBoom(const std::string& name = "BulletCarrotBoom");
	~BulletCarrotBoom() override = default;
	BulletCarrotBoom(const BulletCarrotBoom&) = delete;
	BulletCarrotBoom(BulletCarrotBoom&&) = delete;
	BulletCarrotBoom& operator=(const BulletCarrotBoom&) = delete;
	BulletCarrotBoom& operator=(BulletCarrotBoom&&) = delete;

	static BulletCarrotBoom* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;
	void OnDie() override;

	void SetRotation(float value) override;

	sf::FloatRect GetCustomBounds() const override;

	void Flip() override;
};

