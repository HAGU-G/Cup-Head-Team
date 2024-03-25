#pragma once
#include "ObjectBullet.h"
class BulletCarnationBlueSeed : public ObjectBullet
{
protected:

public:
	BulletCarnationBlueSeed(const std::string& name = "BulletCarnationBlueSeed");
	~BulletCarnationBlueSeed() override = default;
	BulletCarnationBlueSeed(const BulletCarnationBlueSeed&) = delete;
	BulletCarnationBlueSeed(BulletCarnationBlueSeed&&) = delete;
	BulletCarnationBlueSeed& operator=(const BulletCarnationBlueSeed&) = delete;
	BulletCarnationBlueSeed& operator=(BulletCarnationBlueSeed&&) = delete;

	static BulletCarnationBlueSeed* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;
	void OnDie() override;

	void SetRotation(float value) override;

	void Flip() override;
	void Frie();
	sf::FloatRect GetCustomBounds() const;
};

