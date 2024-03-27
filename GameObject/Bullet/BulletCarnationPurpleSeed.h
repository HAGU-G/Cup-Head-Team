#pragma once
#include "ObjectBullet.h"

class BulletCarnationPurpleSeed : public ObjectBullet
{
protected:
	
public:
	BulletCarnationPurpleSeed(const std::string& name = "BulletCarnationPurpleSeed");
	~BulletCarnationPurpleSeed() override = default;
	BulletCarnationPurpleSeed(const BulletCarnationPurpleSeed&) = delete;
	BulletCarnationPurpleSeed(BulletCarnationPurpleSeed&&) = delete;
	BulletCarnationPurpleSeed& operator=(const BulletCarnationPurpleSeed&) = delete;
	BulletCarnationPurpleSeed& operator=(BulletCarnationPurpleSeed&&) = delete;

	static BulletCarnationPurpleSeed* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;
	void SetRotation(float value)override;
	void OnDie() override;

	void PlaySfx();

	sf::RectangleShape GetCustomBounds() const override;
};

