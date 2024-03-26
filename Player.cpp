#include "pch.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet/BulletPeashot.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{
}

Player::~Player()
{
}

void Player::Init()
{
	SpriteGo::Init();

	animator.SetTarget(&sprite);
	hasHitBox = true;
	prePosition = position;
}

void Player::Reset()
{
	scene = SCENE_MGR.GetCurrentScene();
	hp = maxHp;
	animator.Play("animations/PlayerIdle.csv");
	SetOrigin(Origins::BC);
	prePosition = position;
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);


	if (state == PlayerState::Dead)
	{
		return;
	}

	float horizontalInput = InputMgr::GetAxisRaw(Axis::Horizontal);
	bool isDownKeyPressed = InputMgr::GetKey(sf::Keyboard::Down);
	isCKeyPressed = InputMgr::GetKey(sf::Keyboard::C);

	if (isInvincible)                                      //무적 상태 o
	{
		invincibilityTimer += dt;
		if (invincibilityTimer >= invincibilityDuration)
		{
			isDamaging = false;
			isInvincible = false;                          //무적 상태 x
			invincibilityTimer = 0.0f;
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::LShift) && !isDashing)
	{
		animator.Play("animations/PlayerDash.csv");
		isDashing = true;
		dashTimer = dashDuration;
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::LShift))
	{
		animator.Play("animations/PlayerIdle.csv");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		animator.Play("animations/PlayerJump.csv");

		isJumping = true;

		if (isGrounded)
		{
			isGrounded = false;
			velocity.y = -700.f;
		}
	}

	if (isDashing)
	{
		Dash(dt);
	}
	else
	{
		velocity.x = horizontalInput * speed;
		velocity.y += gravity * dt;

		if (!((isDownKeyPressed || isCKeyPressed) && isGrounded) || isJumping)
		{
			velocity.x = horizontalInput * speed;
		}
		else
		{
			velocity.x = 0;
		}


		position += velocity * dt;

		if (position.y > 0.f)
		{
			isGrounded = true;
			isJumping = false;
			isParry = false;
			position.y = 0.f;
			velocity.y = 0.f;
		}
		UpdateDirection(horizontalInput, dt);

		SetPosition(position);

		if (horizontalInput != 0.f)
		{
			SetFlipX(horizontalInput < 0);
		}

		fireTimer += dt;
		if (InputMgr::GetKey(sf::Keyboard::X) && fireTimer > fireIntervel)
		{
			isFire = true;
			fireTimer = 0.f;
			Fire(currentDirection);
		}

		if (InputMgr::GetKeyUp(sf::Keyboard::X))
		{
			isFire = false;
		}
	}


	auto bounds = sprite.getGlobalBounds();
	float shrinkFactor = 0.7f;
	float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
	float heightReduction = bounds.height * (1 - shrinkFactor) / 2;
	customBounds.setSize({ bounds.width * shrinkFactor, bounds.height * shrinkFactor });
	customBounds.setPosition(bounds.left + widthReduction, bounds.top + heightReduction);

	MoveDirection = position - prePosition;
	prePosition = position;
}

void Player::UpdateDirection(float horizontalInput, float dt)
{

	if (isJumping)
	{
		UpdateJumpingDirection(horizontalInput, InputMgr::GetAxisRaw(Axis::Vertical));
		return;
	}

	float verticalInput = InputMgr::GetAxisRaw(Axis::Vertical);

	if (isCKeyPressed && !isDamaging)
	{
		if (horizontalInput > 0.f)
		{
			if (verticalInput > 0.f)
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerAimSideDown.csv")
				{
					animator.Play("animations/PlayerAimSideDown.csv");
				}
				currentDirection = Direction::RightDown;
			}
			else if (verticalInput < 0.f)
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerAimSideUp.csv")
				{
					animator.Play("animations/PlayerAimSideUp.csv");
				}
				currentDirection = Direction::RightUp;
			}
			else
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerAimStraight.csv")
				{
					animator.Play("animations/PlayerAimStraight.csv");
				}
				currentDirection = Direction::Right;
			}
		}
		else if (horizontalInput < 0.f)
		{
			if (verticalInput > 0.f)
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerAimSideDown.csv")
				{
					animator.Play("animations/PlayerAimSideDown.csv");
				}
				currentDirection = Direction::LeftDown;
			}
			else if (verticalInput < 0.f)
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerAimSideUp.csv")
				{
					animator.Play("animations/PlayerAimSideUp.csv");
				}
				currentDirection = Direction::LeftUp;
			}
			else
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerAimStraight.csv")
				{
					animator.Play("animations/PlayerAimStraight.csv");
				}
				currentDirection = Direction::Left;
			}
		}
		else if (verticalInput > 0.f)
		{
			if (animator.GetCurrentCilpId() != "animations/PlayerAimDown.csv")
			{
				animator.Play("animations/PlayerAimDown.csv");
			}

			currentDirection = Direction::Down;
		}
		else if (verticalInput < 0.f)
		{
			if (animator.GetCurrentCilpId() != "animations/PlayerAimUp.csv")
			{
				animator.Play("animations/PlayerAimUp.csv");
			}
			currentDirection = Direction::Up;
		}
	}
	else if (!isCKeyPressed && !isDamaging)
	{
		// C 키x, 방향은 변경o, 
		if (InputMgr::GetKey(sf::Keyboard::X) && horizontalInput == 0)
		{
			if (animator.GetCurrentCilpId() != "animations/PlayerShootStraight.csv")
			{
				animator.Play("animations/PlayerShootStraight.csv");
			}
		}
		else if (horizontalInput > 0.f)
		{
			currentDirection = verticalInput < 0.f ? Direction::RightUp : Direction::Right;
			if (animator.GetCurrentCilpId() != "animations/PlayerRun.csv" && !isFire)
			{
				animator.Play("animations/PlayerRun.csv");
			}
			else if (animator.GetCurrentCilpId() != "animations/playerrunshooting.csv" && isFire && !isCKeyPressed && (currentDirection == Direction::Right || currentDirection == Direction::Left) && !isJumping)
			{
				animator.Play("animations/playerrunshooting.csv");
			}
			else if (animator.GetCurrentCilpId() != "animations/playersideshooting.csv" && isFire && !isCKeyPressed && (currentDirection == Direction::RightUp || currentDirection == Direction::LeftUp) && !isJumping)
			{
				animator.Play("animations/playersideshooting.csv");
			}
		}
		else if (horizontalInput < 0.f)
		{
			currentDirection = verticalInput < 0.f ? Direction::LeftUp : Direction::Left;
			if (animator.GetCurrentCilpId() != "animations/PlayerRun.csv" && !isFire)
			{
				animator.Play("animations/PlayerRun.csv");
			}
			else if (animator.GetCurrentCilpId() != "animations/playerrunshooting.csv" && isFire && !isCKeyPressed && (currentDirection == Direction::Right || currentDirection == Direction::Left) && !isJumping)
			{
				animator.Play("animations/playerrunshooting.csv");
			}
			else if (animator.GetCurrentCilpId() != "animations/playersideshooting.csv" && isFire && !isCKeyPressed && (currentDirection == Direction::RightUp || currentDirection == Direction::LeftUp) && !isJumping)
			{
				animator.Play("animations/playersideshooting.csv");
			}
		}
		else
		{
			if (animator.GetCurrentCilpId() != "animations/PlayerIdle.csv")
			{
				animator.Play("animations/PlayerIdle.csv");
			}
		}
	}

	if (!isJumping && !isCKeyPressed && InputMgr::GetKey(sf::Keyboard::Down))
	{
		if (animator.GetCurrentCilpId() != "animations/PlayerDuck.csv")
		{
			animator.Play("animations/PlayerDuck.csv");
		}
	}

	SetOrigin(Origins::BC);
}

void Player::UpdateJumpingDirection(float horizontalInput, float verticalInput)
{

	if (horizontalInput > 0.f)
	{
		currentDirection = verticalInput > 0.f ? Direction::RightDown : verticalInput < 0.f ? Direction::RightUp : Direction::Right;
	}
	else if (horizontalInput < 0.f)
	{
		currentDirection = verticalInput > 0.f ? Direction::LeftDown : verticalInput < 0.f ? Direction::LeftUp : Direction::Left;
	}
	else
	{
		currentDirection = verticalInput > 0.f ? Direction::Down : verticalInput < 0.f ? Direction::Up : currentDirection;
	}
}

void Player::Fire(Direction dir)
{
	sf::Vector2f pos = position;                 //손가락 포지션 변경 필요

	const float random = 20.f;                   //약간의 랜덤 방향으로 발사
	int temp = rand();
	switch (dir)
	{
	case Direction::Right:
		pos.x += 50.f;
		pos.y += (rand() % static_cast<int>(random * 2 + 1)) - random;
		break;
	case Direction::Left:
		pos.x -= 50.f;
		pos.y += (rand() % static_cast<int>(random * 2 + 1)) - random;
		break;
	case Direction::Up:
		pos.x += (rand() % static_cast<int>(random * 2 + 1)) - random;
		pos.y -= 60.f;
		break;
	case Direction::Down:
		pos.x += (rand() % static_cast<int>(random * 2 + 1)) - random;
		pos.y += 60.f;
		break;
	case Direction::RightUp:
		pos.x += (temp % static_cast<int>(random * 2 + 1)) - random + 30;
		pos.y += (temp % static_cast<int>(random * 2 + 1)) - random - 30;
		break;
	case Direction::LeftDown:
		pos.x += (temp % static_cast<int>(random * 2 + 1)) - random - 30;
		pos.y += (temp % static_cast<int>(random * 2 + 1)) - random + 30;
		break;
	case Direction::LeftUp:
		pos.x += (rand() % static_cast<int>(random * 2 + 1)) - random - 30;
		pos.y += (rand() % static_cast<int>(random * 2 + 1)) - random - 30;
		break;
	case Direction::RightDown:
		pos.x += (rand() % static_cast<int>(random * 2 + 1)) - random + 30;
		pos.y += (rand() % static_cast<int>(random * 2 + 1)) - random + 30;
		break;
	}
	pos.y -= 100;
	BulletPeashot::Create(pos, dir, scene);
}

void Player::Dash(float dt)
{
	if (dashTimer > 0)
	{
		sf::Vector2f dashDirection;
		switch (currentDirection)
		{
		case Direction::Right:
			dashDirection = sf::Vector2f(1, 0);
			break;
		case Direction::Left:
			dashDirection = sf::Vector2f(-1, 0);
			break;

		}

		SetPosition(position + dashDirection * dashSpeed * dt);
		dashTimer -= dt;
	}
	else
	{
		isDashing = false;
	}
}

void Player::OnDamage()
{

	hp -= 1;
	std::cout << "On" << std::endl;
	if (hp == 0)
	{
		OnDie();
	}
}

void Player::OnDie()
{
	animator.Play("animations/PlayerDie.csv");
	state = PlayerState::Dead;
}

void Player::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);

	auto monsters = sceneGame->getAllMonsters();
	for (auto& monster : monsters)
	{
		if (monster != nullptr && monster->IsAlive() && GetCustomBounds().getGlobalBounds().intersects(monster->GetCustomBounds().getGlobalBounds()))
		{
			if (isJumping && monster->GetPink())
			{
				//패링
				if (!isParry)
				{
					animator.Play("animations/PlayerParry.csv");
					animator.PlayQueue("animations/PlayerJump.csv");
					isParry = true;
					isGrounded = false;
					velocity.y = -500.f;
					std::cout << "Parry" << std::endl;
				}
			}
			else if (!isInvincible)
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerDamage.csv")
				{
					animator.Play("animations/PlayerDamage.csv");
				}
				isDamaging = true;
				isInvincible = true;
				invincibilityTimer = 0.0f;
				OnDamage();
			}

		}
	}

	auto toeholds = sceneGame->getAlltoehold();
	for (auto& toehold : toeholds)
	{
		if (position.y <= toehold->GetCustomBoundsRect().top)
		{
			toehold->onToehold = true;
		}
		if (toehold != nullptr && toehold->GetActive() && 
			MoveDirection.y >= 0 && toehold->onToehold &&
			(toehold->GetCustomBoundsRect().left <= this->GetGlobalBounds().left + this->GetGlobalBounds().width)&&
			(toehold->GetCustomBoundsRect().left + toehold->GetCustomBoundsRect().width >= this->GetGlobalBounds().left))
		{
			if (this->GetGlobalBounds().intersects(toehold->GetCustomBoundsRect()))
			{
				
				position.y = toehold->GetCustomBoundsRect().top;
				velocity.y = 0;
				isGrounded = true;
				isJumping = false;
			}
		}
		if (position.y > toehold->GetCustomBoundsRect().top+gravity*dt)
		{
			toehold->onToehold = false;
		}
	}
}



