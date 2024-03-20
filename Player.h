#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class Player : public SpriteGo
{
protected:
	Animator animator;
	Direction currentDirection = Direction::Right;
	Direction PreDirection = Direction::Right;

	float gravity = 800.f;
	float speed = 500.f;

	float parryDamage = 100.f;

	float dashSpeed = 1000.0f;  
	bool isDashing = false;     
	float dashDuration = 0.2f; 
	float dashTimer = 0.0f;    

	sf::Vector2f velocity;
	sf::Vector2f fireDir;

	bool isGrounded = true;
	bool isAlive = true;
	bool isFire = false;
	bool isJumping = false;
	bool isCKeyPressed;

	int maxHp = 3;
	int hp;

	float horizontalInput;
public:
	Player(const std::string& name = "");
	~Player() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

	void UpdateDirection(float horizontalInput, float dt);
	void UpdateJumpingDirection(float horizontalInput, float verticalInput);

	void Fire(Direction direction);
	int GetHp() { return hp; }
	void ReSetHp() { hp = maxHp; }
	void Dash(float dt);

	void OnDamage();
	void OnDie();



};