#include "pch.h"
#include "Player.h"
#include "SceneDev2.h"
#include "Bullet/ObjectBullet.h"
#include <Windows.h>

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
	
	float h = InputMgr::GetAxisRaw(Axis::Horizontal);

	if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		if(isGrounded)
		{
			isGrounded = false;
			velocity.y = -300.f;
			SetTexture("resource/cuphead_jump_0001.png");
			SetOrigin(Origins::BC);
		}
	}

	velocity.x = h * speed;
	velocity.y += gravity * dt;

	position += velocity * dt;

	if (position.y > 0.f)
	{
		isGrounded = true;
		position.y = 0.f;
		velocity.y = 0.f;
	}

	SetPosition(position);

	if (isGrounded && InputMgr::GetKeyUp(sf::Keyboard::Z))
	{
		SetTexture("resource/cuphead_idle_0001.png");
		SetOrigin(Origins::BC);
	}
	
	if (h != 0.f)
	{
		SetFlipX(h < 0);
	}

	if (InputMgr::GetAxisRaw(Axis::Horizontal) > 0.f)
	{
		if (InputMgr::GetAxisRaw(Axis::Vertical) > 0.f)
		{
			currentDirection = Direction::RightDown;
		}
		else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
		{
			currentDirection = Direction::RightUp;
		}
		else
		{
			currentDirection = Direction::Right;
		}
		PreDirection = Direction::Right;
	}
	else if (InputMgr::GetAxisRaw(Axis::Horizontal) < 0.f)
	{
		if (InputMgr::GetAxisRaw(Axis::Vertical) > 0.f)
		{
			currentDirection = Direction::LeftDown;
		}
		else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
		{
			currentDirection = Direction::LeftUp;
		}
		else
		{
			currentDirection = Direction::Left;
		}
		PreDirection = Direction::Left;
	}
	else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
	{
		currentDirection = Direction::Up;
	}
	else if (InputMgr::GetAxisRaw(Axis::Vertical) > 0.f)
	{
		currentDirection = Direction::Down;
	}
	else
	{
		currentDirection = PreDirection;
	}

	if (/*isFire && */InputMgr::GetKeyDown(sf::Keyboard::X))
	{
		Fire(currentDirection);
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Player::Fire(Direction direction)
{
	sf::Vector2f pos = position;                 //손가락 포지션 변경
	pos.y -= 100;
	ObjectBullet::Create(pos, direction, sceneDev2);
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



std::wstring Player::SelectFile()
{
	wchar_t save[260];
	GetCurrentDirectory(MAX_PATH, save);


	OPENFILENAME ofn;
	wchar_t szFile[260];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = L'\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All Files\0*.*\0Text Files\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		SetCurrentDirectory(save);
		return ofn.lpstrFile;
	}
	else
	{
		SetCurrentDirectory(save);
		return L"";
	}
}