#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class SceneDev2;

class Player :  public SpriteGo
{
protected:
	/*Animator animator;*/
	SceneDev2* sceneDev2 = nullptr;

	float gravity = 500.f;
	float speed = 500.f;
	
	sf::Vector2f velocity;
	sf::Vector2f fireDir;

	bool isGrounded = true;
	bool isAlive = true;
	bool isFire = false;

	int maxHp = 3;
	int hp;

public:
	Player(const std::string& name = "");
	~Player() override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	void Draw(sf::RenderWindow& window);

	void Fire(sf::Vector2f direction);
	int GetHp() { return hp; }
	void ReSetHp() { hp = maxHp; }

	void OnDamage();
	void OnDie();

};

