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

	SetTexture("resource/cuphead_idle_0001.png");
	SetOrigin(Origins::BC);
	SetPosition({0,0});

	hasHitBox = true;
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	scene = SCENE_MGR.GetCurrentScene();
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	float horizontalInput = InputMgr::GetAxisRaw(Axis::Horizontal);
	bool isDownKeyPressed = InputMgr::GetKey(sf::Keyboard::Down);
	isCKeyPressed = InputMgr::GetKey(sf::Keyboard::C);


	if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		isJumping = true;

		if (isGrounded)
		{
			isGrounded = false;
			velocity.y = -500.f;
		}
	}

	velocity.x = horizontalInput * speed;
	velocity.y += gravity * dt;

	if (!((isDownKeyPressed || isCKeyPressed) && isGrounded)|| isJumping)
	{
		SetTexture("resource/cuphead_idle_0001.png");
		SetOrigin(Origins::BC);
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

	SetPosition(position);

	if (horizontalInput != 0.f)
	{
		SetFlipX(horizontalInput < 0);
	}

	UpdateDirection(horizontalInput, dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::X))
	{
		Fire(currentDirection);
	}
	
}

void Player::UpdateDirection(float horizontalInput, float dt)
{
	if (isJumping)
	{
		SetTexture("resource/cuphead_jump_0001.png");
		UpdateJumpingDirection(horizontalInput, InputMgr::GetAxisRaw(Axis::Vertical));
		return; 
	}

	float verticalInput = InputMgr::GetAxisRaw(Axis::Vertical);

	if (isCKeyPressed)
	{
		if (horizontalInput > 0.f)
		{
			if (verticalInput > 0.f)
			{
				SetTexture("resource/cuphead_aim_diagonal_down_0001.png");
				currentDirection = Direction::RightDown;
			}
			else if (verticalInput < 0.f)
			{
				SetTexture("resource/cuphead_aim_diagonal_up_0001.png");
				currentDirection = Direction::RightUp;
			}
			else
			{
				SetTexture("resource/cuphead_aim_straight_0001.png");
				currentDirection = Direction::Right;
			}
		}
		else if (horizontalInput < 0.f)
		{
			if (verticalInput > 0.f)
			{
				SetTexture("resource/cuphead_aim_diagonal_down_0001.png");
				currentDirection = Direction::LeftDown;
			}
			else if (verticalInput < 0.f)
			{
				SetTexture("resource/cuphead_aim_diagonal_up_0001.png");
				currentDirection = Direction::LeftUp;
			}
			else
			{
				SetTexture("resource/cuphead_aim_straight_0001.png");
				currentDirection = Direction::Left;
			}
		}
		else if (verticalInput > 0.f)
		{
			SetTexture("resource/cuphead_aim_down_0001.png");
			currentDirection = Direction::Down;
		}
		else if (verticalInput < 0.f)
		{
			SetTexture("resource/cuphead_aim_up_0001.png");
			currentDirection = Direction::Up;
		}
	}
	else
	{
		// C 키x, 방향은 변경o 텍스처는 변경x
		if (horizontalInput > 0.f)
		{
			currentDirection = verticalInput < 0.f ? Direction::RightUp : Direction::Right;
		}
		else if (horizontalInput < 0.f)
		{
			currentDirection = verticalInput < 0.f ? Direction::LeftUp : Direction::Left;
		}
		else if (verticalInput < 0.f)
		{
			currentDirection = Direction::Up;
		}
	}
	if (!isJumping && !InputMgr::GetKey(sf::Keyboard::C) && InputMgr::GetKey(sf::Keyboard::Down))
	{
		SetTexture("resource/cuphead_duck_0004.png");
	}


	if (!InputMgr::GetKey(sf::Keyboard::C) && isGrounded && horizontalInput == 0 && verticalInput == 0) 
	{
		SetTexture("resource/cuphead_idle_0001.png");
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

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Player::Fire(Direction dir)
{
	sf::Vector2f pos = position;                 //손가락 포지션 변경 필요

	const float random = 20.f;                   //약간의 랜덤 방향으로 발사
	int temp = rand();
	switch (dir)
	{
	case Direction::Right:
	case Direction::Left:
		pos.y += (rand() % static_cast<int>(random * 2 + 1)) - random;
		break;
	case Direction::Up:
	case Direction::Down:
		pos.x += (rand() % static_cast<int>(random * 2 + 1)) - random;
		break;
	case Direction::RightUp:
	case Direction::LeftDown:
		pos.x += (temp % static_cast<int>(random * 2 + 1)) - random;
		pos.y += (temp % static_cast<int>(random * 2 + 1)) - random;
		break;
	case Direction::RightDown:
	case Direction::LeftUp:
		pos.x += (temp % static_cast<int>(random * 2 + 1)) - random;
		pos.y += (temp % static_cast<int>(random * 2 + 1)) - random;
		break;
	}

	pos.y -= 100;
	BulletPeashot::Create(pos, dir, scene);
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



