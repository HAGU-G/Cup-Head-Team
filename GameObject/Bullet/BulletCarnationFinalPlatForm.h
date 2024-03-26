#pragma once
#include "ObjectBullet.h"
class BulletCarnationFinalPlatForm : public ObjectBullet
{
protected:
	bool timer = false;
	float attackTimer = 0.f;

	bool retrunStart = false;
	bool returnTimer = 0.f;
public:
	BulletCarnationFinalPlatForm(const std::string& name = "BulletCarnationFinalPlatForm");
	~BulletCarnationFinalPlatForm() override = default;
	BulletCarnationFinalPlatForm(const BulletCarnationFinalPlatForm&) = delete;
	BulletCarnationFinalPlatForm(BulletCarnationFinalPlatForm&&) = delete;
	BulletCarnationFinalPlatForm& operator=(const BulletCarnationFinalPlatForm&) = delete;
	BulletCarnationFinalPlatForm& operator=(BulletCarnationFinalPlatForm&&) = delete;

	static BulletCarnationFinalPlatForm* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;
	void OnDie() override;

	void BackVine();
	void TimerStart();
	void Attack();
	void ReturnStart();
	void ReturnVine();
	void Die();

	sf::FloatRect GetCustomBounds() const override;
	void SetRotation(float value);
};

