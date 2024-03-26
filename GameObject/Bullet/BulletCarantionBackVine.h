#pragma once
#include "ObjectBullet.h"
class BulletCarantionBackVine : public ObjectBullet
{
protected:
	bool timer = false;
	float attackTimer = 0.f;

	bool retrunStart = false;
	bool returnTimer = 0.f;
public:
	BulletCarantionBackVine(const std::string& name = "BulletCarantionBackVine");
	~BulletCarantionBackVine() override = default;
	BulletCarantionBackVine(const BulletCarantionBackVine&) = delete;
	BulletCarantionBackVine(BulletCarantionBackVine&&) = delete;
	BulletCarantionBackVine& operator=(const BulletCarantionBackVine&) = delete;
	BulletCarantionBackVine& operator=(BulletCarantionBackVine&&) = delete;

	static BulletCarantionBackVine* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;
	void OnDie() override;

	void TimerStart();
	void Attack();
	void ReturnStart();
	void ReturnVine();
	void Die();

	sf::RectangleShape GetCustomBounds() const override;
	void SetRotation(float value);
};

