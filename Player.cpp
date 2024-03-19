#include "pch.h"
#include "Player.h"
#include "SceneDev2.h"
#include "Bullet/ObjectBullet.h"

// �ؾ��ϴ� �� 
// �÷��̾� Ű �Էº� �ؽ��� ��ȯ (�Ϸ�)
// z(����) ���¿��� Ư�� �ؽ��Ŀ� ��ġ�� �ѹ��� z(����) ���� (�̿� : ���� ���� ���� ����)
// cŰ : �̵� x, ���� ����  (�Ϸ�)
// ���� �ణ�� ���� �߰� (�Ϸ�)

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
				if (/*��ȫ ��ü�� �浹 �� && */InputMgr::GetKeyDown(sf::Keyboard::Z))
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
	sf::Vector2f pos = position;                 //�հ��� ������ ���� �ʿ�

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
	/*������ �ִϸ��̼� ���*/
	hp -= 1;

	if (hp == 0)
	{
		OnDie();
	}
}

void Player::OnDie()
{
	/*��� �ִϸ��̼� ���*/
	isAlive = false;
}



