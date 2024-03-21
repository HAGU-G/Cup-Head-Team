#pragma once
#include "ObjectBullet.h"
#include "Monster/BossPotato.h"

class SceneDev2; /////////////////////////////////////////

class BulletPeashot : public ObjectBullet
{
protected:
	BossPotato* bossPotato;                                 //////////////////////
	SceneDev2* sceneDev2;                                  /////////////////////////////////////////

public:
	BulletPeashot(const std::string& name = "BulletPeashot");
	~BulletPeashot() override = default;
	BulletPeashot(const BulletPeashot&) = delete;
	BulletPeashot(BulletPeashot&&) = delete;
	BulletPeashot& operator=(const BulletPeashot&) = delete;
	BulletPeashot& operator=(BulletPeashot&&) = delete;

	static BulletPeashot* Create(const sf::Vector2f& pos, Direction direction, Scene* scene);
	static BulletPeashot* Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Init() override;
	void Reset() override;

	void Update(float dt) override;

	void OnCreate() override;
	void OnDie() override;
};

