#pragma once
#include "SpriteGo.h"
class ObjectMonster : public SpriteGo
{
protected:
	int maxHp = 100;
	int hp = 100;

	float hitEffectTimer = 0.f;
	float hitEffectDuration = 0.1f;

	sf::Shader shaderHit;

	ObjectMonster(const std::string& name = "Monster");			//상속받아서 새 클래스 만들어주세요.
public:
	~ObjectMonster() override = default;
	ObjectMonster(const ObjectMonster&) = delete;
	ObjectMonster(ObjectMonster&&) = delete;
	ObjectMonster& operator=(const ObjectMonster&) = delete;
	ObjectMonster& operator=(ObjectMonster&&) = delete;

	void Init() override;
	void Update(float dt) override;
	void Reset() override;

	virtual bool OnDamage(int damage);
	virtual bool CollisionCheck() = 0;

	inline int GetHp() const { return hp; }
	inline int GetMaxHp() const { return hp; }
};

