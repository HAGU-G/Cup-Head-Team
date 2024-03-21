#include "pch.h"
#include "Player.h"
#include "SceneDev2.h"
#include "Bullet/BulletPeashot.h"

// 해야하는 일 
// 플레이어 키 입력별 텍스쳐 변환 (완료)
// z(점프) 상태에서 특정 텍스쳐와 겹치면 한번더 z(점프) 가능 (미완 : 현재 무한 점프 가능)
// c키 : 이동 x, 조준 가능  (완료)
// 공격 약간의 랜덤 추가 (완료)

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

	/*SetTexture("resource/cuphead_idle_0001.png");
	SetOrigin(Origins::BC);
	SetPosition({0,0});*/

	animator.SetTarget(&sprite);
	hasHitBox = true;

}

void Player::Reset()
{
	scene = SCENE_MGR.GetCurrentScene();

	animator.Play("animations/PlayerIdle.csv");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f,0.f });
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	float horizontalInput = InputMgr::GetAxisRaw(Axis::Horizontal);
	bool isDownKeyPressed = InputMgr::GetKey(sf::Keyboard::Down);
	isCKeyPressed = InputMgr::GetKey(sf::Keyboard::C);


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
			velocity.y = -500.f;
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

		if (!((isDownKeyPressed || isCKeyPressed) && isGrounded)|| isJumping)
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
		
		if (InputMgr::GetKeyUp(sf::Keyboard::X) )
		{
			isFire = false;
		}
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

	if (isCKeyPressed)
	{
		if (horizontalInput > 0.f)
		{
			if (verticalInput > 0.f )
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
	else
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
	/*데미지 애니메이션 출력*/
	hp -= 1;

	if (hp == 0)
	{
		OnDie();
	}
}

void Player::OnDie()
{
	/*사망 애니매이션 출력*/
	isAlive = false;
}



