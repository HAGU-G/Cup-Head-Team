#pragma once
#include "ObjectBullet.h"
class BulletCarnationPollen : public ObjectBullet
{
protected:
	float fireTimer = 0.f;
	int i = 0;

public:
	BulletCarnationPollen(const std::string& name = "BulletCarnationPollen");
	~BulletCarnationPollen() override = default;
	BulletCarnationPollen(const BulletCarnationPollen&) = delete;
	BulletCarnationPollen(BulletCarnationPollen&&) = delete;
	BulletCarnationPollen& operator=(const BulletCarnationPollen&) = delete;
	BulletCarnationPollen& operator=(BulletCarnationPollen&&) = delete;

	static BulletCarnationPollen* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene, int i);

	void Update(float dt) override;
	void Init() override;
	void OnDie() override;

	sf::FloatRect GetCustomBounds() const override;
	int SetColor(int i) { return this->i = i; }
};

