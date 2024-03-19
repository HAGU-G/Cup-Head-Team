#include "pch.h"
#include "Player.h"
#include "SceneDev2.h"

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
	SetOrigin(Origins::BC);
	SetPosition({ 0, 0 });
	SetTexture("resource/cuphead_idle_0001.png");
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	sceneDev2 = dynamic_cast<SceneDev2*>(SCENE_MGR.GetCurrentScene());
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

	if (h != 0.f)
	{
		SetFlipX(h < 0);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		/*손을 위로*/
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			/*손을 오른쪽 위*/
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			/*손을 왼쪽 위*/
		}
	}
	
	if (!isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		/*손을 아래로*/
		
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			/*손을 오른쪽 아래*/
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			/*손을 왼쪽 아래*/

		}
	}
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		/*엎드려*/
		SetTexture("resource/cuphead_duck_0004.png");
	}

	if (isGrounded && InputMgr::GetKeyUp(sf::Keyboard::Down))
	{
		/*일어서*/
		SetOrigin(Origins::BC);
		SetTexture("resource/cuphead_idle_0001.png");
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		/*손을 왼쪽으로*/
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		/*손을 오른쪽으로*/
	}

	if (isFire && InputMgr::GetKeyDown(sf::Keyboard::X))
	{
		//Fire(fireDir);
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Player::Fire(sf::Vector2f direction)
{

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
