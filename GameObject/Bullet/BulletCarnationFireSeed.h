#pragma once
#include "ObjectBullet.h"

class BulletCarnationFireSeed : public ObjectBullet
{
protected:
	float fireTimer = 0.f;
	int i=0;

public:
	BulletCarnationFireSeed(const std::string& name = "BulletCarnationFireSeed");
	~BulletCarnationFireSeed() override = default;
	BulletCarnationFireSeed(const BulletCarnationFireSeed&) = delete;
	BulletCarnationFireSeed(BulletCarnationFireSeed&&) = delete;
	BulletCarnationFireSeed& operator=(const BulletCarnationFireSeed&) = delete;
	BulletCarnationFireSeed& operator=(BulletCarnationFireSeed&&) = delete;

	static BulletCarnationFireSeed* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, int i);

	void Update(float dt) override;
	void Init() override;
	void OnDie() override;

	sf::FloatRect GetCustomBounds() const override;
	int SetColor(int i) { return this->i = i; }

	void SetRotation(float value) override;
	void Vine();
	void VineReturn();
};

