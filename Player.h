#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class SceneGame;

class Player : public SpriteGo
{

public:
	enum class PlayerState {
		Intro,
		Normal,
		Dead,
		None,
	};

	PlayerState state = PlayerState::Normal;
protected:
	SceneGame* sceneGame;
	Animator animator;
	Direction currentDirection = Direction::Right;
	Direction PreDirection;

	float gravity = 3500.f;
	float speed = 500.f;

	float parryDamage = 100.f;

	bool isDashing = false;     
	float dashSpeed = 1000.0f;  
	float dashDuration = 0.2f; 
	float dashTimer = 0.f;    

	float fireTimer = 0.f;
	float fireIntervel = 0.133f;
	float invincibilityDuration = 1.f;
	float invincibilityTimer = 0.f;
	bool isInvincible = false;
	
	sf::Sound fireSound;
	sf::Vector2f velocity;
	sf::Vector2f fireDir;
	sf::Vector2f prePosition;
	sf::Vector2f MoveDirection;
	bool isDownKeyPressed;
	bool isGrounded = true;
	bool isAlive = true;
	bool isFire = false;
	bool isJumping = false;
	bool isCKeyPressed;
	bool isParry = false;
	bool isDamaging = false;
	bool isIntro = true;
	bool isXKeyPressed = false;
	bool onPlatForm = false;
	bool isDuck = false;
	bool isDucking = false;
	bool invincibleMode = false;
	int maxHp = 3;

	int hp;

	float horizontalInput;
public:
	Player(const std::string& name = "");
	~Player() override;

	void Init() override;
	void Reset() override;
	void Intro();
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void UpdateDirection(float horizontalInput, float dt);
	void UpdateJumpingDirection(float horizontalInput, float verticalInput);

	void Fire(Direction direction);
	int GetHp() { return hp; }
	void ReSetHp() { hp = maxHp; }
	void Dash(float dt);
	void DashEnd();
	void DuckIdle();
	void OnDamage();
	void OnDie();

	bool OnPlatForm();

	void InvincibleMode();
};