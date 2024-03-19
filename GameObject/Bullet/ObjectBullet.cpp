#include "pch.h"
#include "ObjectBullet.h"

ObjectBullet::ObjectBullet(const std::string& name)
	:SpriteGo(name)
{
}

void ObjectBullet::Init()
{
	SetTexture("resource/Sprite/peashot/weapon_peashot_intro_b_0001.png");
	SetOrigin(Origins::ML);
	SetSpeed(300.f);
}

void ObjectBullet::Release()
{

}

void ObjectBullet::Reset()
{
	SpriteGo::Reset();
}

void ObjectBullet::Update(float dt)
{
	Translate(direction * speed * dt);
}

void ObjectBullet::LateUpdate(float dt)
{
	if (moveDistance > range)
	{
		scene->RemoveGo(this);
	}
}

void ObjectBullet::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void ObjectBullet::Create(const sf::Vector2f& pos, Direction direction, Scene* scene)
{
	ObjectBullet* ob = new ObjectBullet();
	ob->Init();
	ob->Reset();
	ob->prePosition = pos;
	ob->SetPosition(pos);
	ob->SetDirection(direction);
	scene->AddGo(ob);
	ob->scene = scene;

}

void ObjectBullet::SetDirection(Direction direction)
{
	switch (direction)
	{
	case Direction::Right:
		this->direction = { 1.f, 0.f };
		break;
	case Direction::RightUp:
		this->direction = Utils::GetNormal({ 1.f, -1.f });
		break;
	case Direction::Up:
		this->direction = { 0.f, -1.f };
		break;
	case Direction::LeftUp:
		this->direction = Utils::GetNormal({ -1.f, -1.f });
		break;
	case Direction::Left:
		this->direction = { -1.f, 0.f };
		break;
	case Direction::LeftDown:
		this->direction = Utils::GetNormal({ -1.f, 1.f });
		break;
	case Direction::Down:
		this->direction = { 0.f, 1.f };
		break;
	case Direction::RightDown:
		this->direction = Utils::GetNormal({ 1.f, 1.f });
		break;
	case Direction::None:
		this->direction = { 0.f, 0.f };
		break;
	}
}

void ObjectBullet::SetPosition(const sf::Vector2f& position)
{
	SpriteGo::SetPosition(position);
	bound.setPosition(position);

	moveDistance += Utils::Distance(prePosition, position);
	prePosition = position;

}
