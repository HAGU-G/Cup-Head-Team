#pragma once
#include "ObjectBullet.h"

class BulletCarnationPinkSeed : public ObjectBullet
{
protected:
	bool right = false;
	bool left = false;

	float moveSpeed = 0.f;
	float attackTimer = 0.f;

	bool timerStart = false;
public:
	BulletCarnationPinkSeed(const std::string& name = "BulletCarnationPinkSeed");
	~BulletCarnationPinkSeed() override = default;
	BulletCarnationPinkSeed(const BulletCarnationPinkSeed&) = delete;
	BulletCarnationPinkSeed(BulletCarnationPinkSeed&&) = delete;
	BulletCarnationPinkSeed& operator=(const BulletCarnationPinkSeed&) = delete;
	BulletCarnationPinkSeed& operator=(BulletCarnationPinkSeed&&) = delete;

	static BulletCarnationPinkSeed* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;
	void OnDie() override;

	void Move();
	void Stop();
	void Attack();
	void TimerStart() { timerStart = true; }
	void Flip() override;
	sf::FloatRect GetCustomBounds() const;
	void SetRotation(float value)override;
};

