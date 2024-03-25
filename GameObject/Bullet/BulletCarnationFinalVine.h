#pragma once
#include "ObjectBullet.h"
class BulletCarnationFinalVine : public ObjectBullet
{
protected:

public:
	BulletCarnationFinalVine(const std::string& name = "BulletCarnationFinalVine");
	~BulletCarnationFinalVine() override = default;
	BulletCarnationFinalVine(const BulletCarnationFinalVine&) = delete;
	BulletCarnationFinalVine(BulletCarnationFinalVine&&) = delete;
	BulletCarnationFinalVine& operator=(const BulletCarnationFinalVine&) = delete;
	BulletCarnationFinalVine& operator=(BulletCarnationFinalVine&&) = delete;

	static BulletCarnationFinalVine* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Update(float dt) override;
	void Init() override;
	void OnDie() override;

	sf::FloatRect GetCustomBounds() const override;
};

