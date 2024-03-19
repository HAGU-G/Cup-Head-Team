#include "pch.h"
#include "Player.h"
#include "SceneDev2.h"
#include "Bullet/ObjectBullet.h"

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
	sceneDev2 = dynamic_cast<SceneDev2*>(scene);
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	float horizontalInput = InputMgr::GetAxisRaw(Axis::Horizontal);
	
	if (!InputMgr::GetKey(sf::Keyboard::C))
	{

		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			if (isGrounded)
			{
				isGrounded = false;
				velocity.y = -500.f;
				SetTexture("resource/cuphead_jump_0001.png");
				SetOrigin(Origins::BC);
			}
			else
			{
				if (/*분홍 객체와 충돌 중 && */InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					/*if(monster.OnDamage(damage,true))
					{

					}*/
					velocity.y = -500.f;
					SetTexture("resource/cuphead_jump_0001.png");
					SetOrigin(Origins::BC);
				}
			}
		}

		velocity.x = horizontalInput * speed;
		velocity.y += gravity * dt;

		position += velocity * dt;

		if (position.y > 0.f)
		{
			isGrounded = true;
			position.y = 0.f;
			velocity.y = 0.f;
		}
	}
	SetPosition(position);

	if (horizontalInput != 0.f)
	{
		SetFlipX(horizontalInput < 0);
	}

	if (isGrounded)
	{
		SetTexture("resource/cuphead_idle_0001.png");
		SetOrigin(Origins::BC);

		if (InputMgr::GetAxisRaw(Axis::Horizontal) > 0.f)
		{
			SetTexture("resource/cuphead_aim_straight_0001.png");
			if (InputMgr::GetAxisRaw(Axis::Vertical) > 0.f)
			{
				SetTexture("resource/cuphead_aim_diagonal_down_0001.png");
				currentDirection = Direction::RightDown;
			}
			else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
			{
				SetTexture("resource/cuphead_aim_diagonal_up_0001.png");
				currentDirection = Direction::RightUp;
			}
			else
			{
				currentDirection = Direction::Right;
			}
			SetOrigin(Origins::BC);
			PreDirection = Direction::Right;
			isFire = true;
		}
		else if (InputMgr::GetAxisRaw(Axis::Horizontal) < 0.f)
		{
			SetTexture("resource/cuphead_aim_straight_0001.png");
			if (InputMgr::GetAxisRaw(Axis::Vertical) > 0.f)
			{
				SetTexture("resource/cuphead_aim_diagonal_down_0001.png");
				currentDirection = Direction::LeftDown;
			}
			else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
			{
				SetTexture("resource/cuphead_aim_diagonal_up_0001.png");
				currentDirection = Direction::LeftUp;
			}
			else
			{
				currentDirection = Direction::Left;
			}
			SetOrigin(Origins::BC);
			PreDirection = Direction::Left;
			isFire = true;
		}
		else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
		{
			SetTexture("resource/cuphead_aim_up_0001.png");
			SetOrigin(Origins::BC);
			currentDirection = Direction::Up;
			isFire = true;
		}
		else if (InputMgr::GetAxisRaw(Axis::Vertical) > 0.f)
		{
			SetTexture("resource/cuphead_aim_down_0001.png");
			SetOrigin(Origins::BC);
			currentDirection = Direction::Down;
			isFire = true;
		}
		else
		{
			currentDirection = PreDirection;
		}

		if (InputMgr::GetKeyUp(sf::Keyboard::Left) || InputMgr::GetKeyUp(sf::Keyboard::Right) ||
			InputMgr::GetKeyUp(sf::Keyboard::Up) || InputMgr::GetKeyUp(sf::Keyboard::Down))
		{
			SetTexture("resource/cuphead_idle_0001.png");
			SetOrigin(Origins::BC);
			isFire = false;
		}

		if (isFire && InputMgr::GetKeyDown(sf::Keyboard::X))
		{
			Fire(currentDirection);
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Player::Fire(Direction dir)
{
	sf::Vector2f pos = position;                 //손가락 포지션 변경 필요

	const float random = 20.f;
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
	ObjectBullet::Create(pos, dir, sceneDev2);
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



