#include "pch.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet/BulletPeashot.h"
#include "Effect/ObjectEffect.h"

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
	SetOrigin(Origins::BC);
	Intro();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));
}

void Player::Intro()
{
	animator.ClearEvent();
	animator.Play("animations/PlayerIntro.csv");
	state = PlayerState::Intro;
	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), [this] {
		state = PlayerState::Normal;
		});
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	if (state != PlayerState::Normal)
	{
		return;
	}

	float horizontalInput = InputMgr::GetAxisRaw(Axis::Horizontal);
	isDownKeyPressed = InputMgr::GetKey(sf::Keyboard::Down);
	isCKeyPressed = InputMgr::GetKey(sf::Keyboard::C);
	isXKeyPressed = InputMgr::GetKey(sf::Keyboard::X);

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
		velocity.x = (PreDirection == Direction::Right ? 1 : -1) * dashSpeed;
		velocity.y = 0;
	}

	if (isDownKeyPressed && InputMgr::GetKeyDown(sf::Keyboard::Z) && isGrounded && onPlatForm)
	{
		isGrounded = false;
		isJumping = true;
		position.y += gravity * dt;
		velocity.y = gravity * dt;

		animator.Play("animations/PlayerJump.csv");
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Z) && !isJumping &&!isDashing)
	{
		animator.Play("animations/PlayerJump.csv");
		isParry = false;
		isJumping = true;

		if (isGrounded)
		{
			isGrounded = false;
			velocity.y = -1400.f;
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
			if (isDownKeyPressed && !isCKeyPressed)
			{
				DuckIdle();
			}
			isGrounded = true;
			isParry = false;
			position.y = 0.f;
			velocity.y = 0.f;
			isJumping = false;
		}
		UpdateDirection(horizontalInput, dt);

		SetPosition(position);

		if (horizontalInput != 0.f)
		{
			SetFlipX(horizontalInput < 0);
		}

		fireTimer += dt;
		if (isXKeyPressed && fireTimer > fireIntervel)
		{
			isFire = true;
			fireTimer = 0.f;
			Fire(currentDirection);
		}
		if (!isXKeyPressed)
		{
			isFire = false;
		}
	}

	if (!isDashing)
	{
		auto bounds = sprite.getGlobalBounds();
		float shrinkFactor = 0.7f;
		float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
		float heightReduction = bounds.height * (1 - shrinkFactor) / 2;
		customBounds.setSize({ bounds.width * shrinkFactor, bounds.height * shrinkFactor });
		customBounds.setPosition(bounds.left + widthReduction, bounds.top + heightReduction);
	}
	else
	{
		auto bounds = sprite.getGlobalBounds();
		float shrinkFactor = 0.1f;
		float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
		float heightReduction = bounds.height * (1 - shrinkFactor) / 2;
		customBounds.setSize({ bounds.width * shrinkFactor, bounds.height * shrinkFactor });
		customBounds.setPosition(bounds.left + widthReduction, bounds.top + heightReduction);
	}

	currentDirection = PreDirection;

	MoveDirection = position - prePosition;
	prePosition = position;

	if (position.x <= -580.f)
	{
		position.x = -580.f;
	}
	else if (position.x >= 580.f)
	{
		position.x = 580.f;
	}
}

void Player::UpdateDirection(float horizontalInput, float dt)
{

	if (isJumping)
	{
		UpdateJumpingDirection(horizontalInput, InputMgr::GetAxisRaw(Axis::Vertical));
		return;
	}

	float verticalInput = InputMgr::GetAxisRaw(Axis::Vertical);

	if (isCKeyPressed && !isDamaging && !isDuck)
	{
		if (isXKeyPressed && isCKeyPressed)
		{
			if (verticalInput < 0.f && horizontalInput == 0)
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerShootUp.csv")
				{
					animator.Play("animations/PlayerShootUp.csv");
				}
				currentDirection = Direction::Up;
			}
			else if (horizontalInput == 0 && verticalInput == 0)
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerShootStraight.csv")
				{
					animator.Play("animations/PlayerShootStraight.csv");
				}
				if (currentDirection == Direction::Right)
				{
					PreDirection = Direction::Right;
				}
				else if (currentDirection == Direction::Left)
				{
					PreDirection = Direction::Left;
				}
			}
			else if (horizontalInput > 0.f)
			{
				if (verticalInput > 0.f)
				{
					if (animator.GetCurrentCilpId() != "animations/PlayerSideDown.csv")
					{
						animator.Play("animations/PlayerSideDown.csv");
					}
					currentDirection = Direction::RightDown;
				}
				else if (verticalInput < 0.f)
				{
					if (animator.GetCurrentCilpId() != "animations/PlayerSideUp.csv")
					{
						animator.Play("animations/PlayerSideUp.csv");
					}
					currentDirection = Direction::RightUp;
				}
				else
				{
					if (animator.GetCurrentCilpId() != "animations/PlayerShootStraight.csv")
					{
						animator.Play("animations/PlayerShootStraight.csv");
					}
					PreDirection = Direction::Right;
				}
				PreDirection = Direction::Right;
			}
			else if (horizontalInput < 0.f)
			{
				if (verticalInput > 0.f)
				{
					if (animator.GetCurrentCilpId() != "animations/PlayerSideDown.csv")
					{
						animator.Play("animations/PlayerSideDown.csv");
					}
					currentDirection = Direction::LeftDown;
				}
				else if (verticalInput < 0.f)
				{
					if (animator.GetCurrentCilpId() != "animations/PlayerSideUp.csv")
					{
						animator.Play("animations/PlayerSideUp.csv");
					}
					currentDirection = Direction::LeftUp;
				}
				else
				{
					if (animator.GetCurrentCilpId() != "animations/PlayerShootStraight.csv")
					{
						animator.Play("animations/PlayerShootStraight.csv");
					}
					PreDirection = Direction::Left;
				}
				PreDirection = Direction::Left;
			}
			else if (verticalInput < 0.f && horizontalInput == 0)
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerShootUp.csv")
				{
					animator.Play("animations/PlayerShootUp.csv");
				}
				currentDirection = Direction::Up;
			}
			else if (verticalInput > 0.f && horizontalInput == 0)
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerShootDown.csv")
				{
					animator.Play("animations/PlayerShootDown.csv");
				}
				currentDirection = Direction::Down;
			}
		}
		if (!isXKeyPressed && isCKeyPressed)
		{
			if (verticalInput < 0.f && horizontalInput == 0)
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerAimUp.csv")
				{
					animator.Play("animations/PlayerAimUp.csv");
				}
				currentDirection = Direction::Up;
			}
			else if (horizontalInput == 0 && verticalInput == 0)
			{
				if (animator.GetCurrentCilpId() != "animations/PlayerAimStraight.csv")
				{
					animator.Play("animations/PlayerAimStraight.csv");
				}
			}
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
					PreDirection = Direction::Right;
					currentDirection = PreDirection;
				}
				PreDirection = Direction::Right;
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
					PreDirection = Direction::Left;
					currentDirection = PreDirection;
				}
				PreDirection = Direction::Left;
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
	}
	if (!isCKeyPressed && !isDamaging && !isDuck)
	{
		// C 키x, 방향은 변경o, 
		if (InputMgr::GetKey(sf::Keyboard::X) && verticalInput < 0.f && horizontalInput == 0)
		{
			if (animator.GetCurrentCilpId() != "animations/PlayerShootUp.csv")
			{
				animator.Play("animations/PlayerShootUp.csv");
			}
			currentDirection = Direction::Up;
		}
		else if (InputMgr::GetKey(sf::Keyboard::X) && horizontalInput == 0 && verticalInput == 0)
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
			if (currentDirection == Direction::Right)
			{
				PreDirection = Direction::Right;
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
			if (currentDirection == Direction::Left)
			{
				PreDirection = Direction::Left;
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

	if (InputMgr::GetKeyDown(sf::Keyboard::Down) && !isJumping && !isCKeyPressed)
	{
		animator.Play("animations/PlayerDuck.csv");
		animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&Player::DuckIdle, this));

	}

	if (InputMgr::GetKey(sf::Keyboard::Down) && !isJumping && !isCKeyPressed)
	{
		if (horizontalInput > 0.f)
		{
			PreDirection = Direction::Right;
		}
		else if(horizontalInput < 0.f)
		{
			PreDirection = Direction::Left;
		}
		isDuck = true;
	}
	else
	{
		isDuck = false;
	}

	SetOrigin(Origins::BC);
}

void Player::UpdateJumpingDirection(float horizontalInput, float verticalInput)
{

	if (horizontalInput > 0.f)
	{
		currentDirection = verticalInput > 0.f ? Direction::RightDown : verticalInput < 0.f ? Direction::RightUp : Direction::Right;
		if (currentDirection == Direction::Right)
		{
			PreDirection = Direction::Right;
		}

	}
	else if (horizontalInput < 0.f)
	{
		currentDirection = verticalInput > 0.f ? Direction::LeftDown : verticalInput < 0.f ? Direction::LeftUp : Direction::Left;
		if (currentDirection == Direction::Left)
		{
			PreDirection = Direction::Left;
		}

	}
	else
	{
		currentDirection = verticalInput > 0.f ? Direction::Down : verticalInput < 0.f ? Direction::Up : currentDirection;
	}
}

void Player::Fire(Direction dir)
{
	sf::Vector2f pos = position; 

	const float random = 20.f;
	int temp = rand();
	switch (dir)
	{
	case Direction::Right:
		if (isDuck)
		{
			pos.x += 80.f;
			pos.y += (rand() % static_cast<int>(random * 2 + 1)) - random + 40.f;
		}
		else
		{
			pos.x += 70.f;
			pos.y += (rand() % static_cast<int>(random * 2 + 1)) - random;
		}
		PreDirection = Direction::Right;
		break;
	case Direction::Left:
		if (isDuck)
		{
			pos.x -= 80.f;
			pos.y += (rand() % static_cast<int>(random * 2 + 1)) - random + 40.f;
		}
		else
		{
			pos.x -= 70.f;
			pos.y += (rand() % static_cast<int>(random * 2 + 1)) - random;
		}
		PreDirection = Direction::Left;
		break;
	case Direction::Up:
		if (PreDirection == Direction::Left)
		{
			pos.x += (rand() % static_cast<int>(random * 2 + 1)) - random - 20.f;
			pos.y -= 80.f;
		}
		else if (PreDirection == Direction::Right)
		{
			pos.x += (rand() % static_cast<int>(random * 2 + 1)) - random + 20.f;
			pos.y -= 80.f;
		}
		break;
	case Direction::Down:
		pos.x += (rand() % static_cast<int>(random * 2 + 1)) - random;
		pos.y += 80.f;
		break;
	case Direction::RightUp:
		pos.x += 45.f;
		pos.y -= 30.f;
		break;
	case Direction::LeftUp:
		pos.x -= 45.f;
		pos.y -= 30.f;
		break;
	case Direction::RightDown:
		pos.x += 40.f;
		pos.y += 55.f;
		break;
	case Direction::LeftDown:
		pos.x -= 40.f;
		pos.y += 55.f;
		break;
	}
	pos.y -= 100;
	BulletPeashot::Create(pos, dir, scene);
}

void Player::Dash(float dt)
{
	if (isDamaging)
	{
		DashEnd();
		return;
	}
	if (PreDirection == Direction::Right)
	{
		velocity.x = dashSpeed;
	}
	else if (PreDirection == Direction::Left)
	{
		velocity.x = -dashSpeed;
	}

	velocity.y = 0;

	animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&Player::DashEnd, this));

	position += velocity * dt;
	SetPosition(position);
}

void Player::DashEnd()
{
	isDashing = false;
	if (isDamaging)
	{
		if (animator.GetCurrentCilpId() != "animations/PlayerDamage.csv")
		{
			animator.Play("animations/PlayerDamage.csv");
		}
	}
	else if (isJumping)
	{
		animator.Play("animations/PlayerJump.csv");
	}
	else
	{
		animator.Play("animations/PlayerIdle.csv");
	}
}

void Player::OnDamage()
{
	hp -= 1;
	if (hp == 0)
	{
		OnDie();
	}
	sceneGame->SetPlayerHp(hp);
}

void Player::DuckIdle()
{
	if(!InputMgr::GetKey(sf::Keyboard::X))
	{
		if (animator.GetCurrentCilpId() != "animations/PlayerDuckIdle.csv")
		{
			animator.Play("animations/PlayerDuckIdle.csv");
		}
	}
	else
	{
		if (animator.GetCurrentCilpId() != "animations/PlayerDuckShoot.csv")
		{
			animator.Play("animations/PlayerDuckShoot.csv");
		}
	}
	
}

void Player::OnDie()
{
	animator.Play("animations/PlayerDie.csv");
	state = PlayerState::Dead;
}

bool Player::OnPlatForm()
{
	if (onPlatForm)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);


	if (state == PlayerState::Dead)
	{
		return;
	}

	for (auto enemyBullet : sceneGame->GetAllEnemyBullet())
	{
		if (enemyBullet->IsAlive() && GetCustomBoundsRect().intersects(enemyBullet->GetCustomBoundsRect()))
		{
			if (isJumping && !isParry && enemyBullet->GetPink())
			{
				//패링
				animator.Play("animations/PlayerParry.csv");
				animator.PlayQueue("animations/PlayerJump.csv");
				isParry = true;
				isGrounded = false;
				velocity.y = -1000.f;
				enemyBullet->OnDamage(1000);
				sceneGame->Pause();
				sceneGame->isParryed = true;
				SOUND_MGR.PlaySfx("resource/sfx_player_parry_slap_0" + std::to_string(Utils::RandomRange(1, 3)) + ".wav");
				ObjectEffect* oe = new ObjectEffect("EffectParry");
				oe->CreateInit((position + enemyBullet->GetPosition()) * 0.5f, MoveDirection, scene);
				oe->GetAnimator().Play("animations/playerParryEffect.csv");
				oe->GetAnimator().AddEvent(oe->GetAnimator().GetCurrentCilpId(), oe->GetAnimator().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));

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
				enemyBullet->OnDamage(1);
			}
		}
	}

	for (auto& monster : sceneGame->GetAllMonsters())
	{
		if (!isInvincible && monster->IsAlive() && GetCustomBoundsRect().intersects(monster->GetCustomBoundsRect()))
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

	for (auto& toehold : sceneGame->GetAlltoehold())
	{
		if (position.y <= toehold->GetCustomBoundsRect().top)
		{
			toehold->onToehold = true;
		}
		if (toehold->GetActive() &&
			toehold->onToehold &&
			(toehold->GetCustomBoundsRect().left <= this->GetGlobalBounds().left + this->GetGlobalBounds().width) &&
			(toehold->GetCustomBoundsRect().left + toehold->GetCustomBoundsRect().width >= this->GetGlobalBounds().left))
		{
			if (MoveDirection.y >= 0)
			{
				if (!(isDownKeyPressed && InputMgr::GetKeyDown(sf::Keyboard::Z)))
				{
					if (this->GetGlobalBounds().intersects(toehold->GetCustomBoundsRect()))
					{

						position.y = toehold->GetCustomBoundsRect().top;
						velocity.y = 0;
						toehold->onPlatForm = onPlatForm = true;
						isGrounded = true;
						isJumping = false;
					}
				}
			}
			else if (isJumping)
			{
				toehold->onPlatForm = onPlatForm = false;
			}
		}
		if (position.y > toehold->GetCustomBoundsRect().top + gravity * dt)
		{
			toehold->onToehold = false;
			toehold->onPlatForm = onPlatForm = false;
			if (MoveDirection.y > 0)
			{
				isGrounded = false;
				isJumping = true;
			}
		}
	}


}



