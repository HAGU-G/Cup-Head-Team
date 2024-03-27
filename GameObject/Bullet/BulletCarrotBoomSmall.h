#pragma once
#include "ObjectBullet.h"
class BulletCarrotBoomSmall : public ObjectBullet
{
protected:

public:
	BulletCarrotBoomSmall(const std::string& name = "BulletCarrotBoomSmall");
	~BulletCarrotBoomSmall() override = default;
	BulletCarrotBoomSmall(const BulletCarrotBoomSmall&) = delete;
	BulletCarrotBoomSmall(BulletCarrotBoomSmall&&) = delete;
	BulletCarrotBoomSmall& operator=(const BulletCarrotBoomSmall&) = delete;
	BulletCarrotBoomSmall& operator=(BulletCarrotBoomSmall&&) = delete;

	static BulletCarrotBoomSmall* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;
	void LateUpdate(float dt) override;
	void SetRotation(float value) override;

	void Flip() override;
};

