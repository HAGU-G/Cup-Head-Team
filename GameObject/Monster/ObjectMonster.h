#pragma once
#include "SpriteGo.h"
class ObjectMonster : public SpriteGo
{
protected:
	int maxHp = 100;
	int hp = 100;

	float hitEffectTimer = 0.f;
	float hitEffectDuration = 0.1f;

	bool isAlive = true;

	sf::Shader shaderHit;

	ObjectMonster(const std::string& name = "Monster");			//상속받아서 새 클래스 만들어주세요.
	bool isPink = false;

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

	inline int GetHp() const { return hp; }
	inline void SetHp(int value) { hp = value; }
	inline int GetMaxHp() const { return hp; }

	bool IsAlive() const { return isAlive; }/////////////////   추가된 부분 입니다.
	bool GetPink() { return isPink; }

//	void SetCustomBounds(float ratio, float ratioY, Origins origin);

	/// <summary>
	/// 0.5초마다 폭발 이펙트 생성
	/// </summary>
	/// <param name="dt"> : deltaTime, 0보다 작을경우 바로 이펙트 생성</param>
	void BossDieEffect(float dt);

};

