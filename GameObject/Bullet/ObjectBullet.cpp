#include "pch.h"
#include "ObjectBullet.h"

ObjectBullet::ObjectBullet(const std::string& name)
	:SpriteGo(name)
{
}

ObjectBullet::~ObjectBullet()
{
	OnDie();
}

void ObjectBullet::Init()
{
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
	SpriteGo::Update(dt);
	Translate(direction * speed * dt);
	if (type == Type::Homing)
	{
		if (doHoming) { Homing(dt); }
		Flip();
	}

}

void ObjectBullet::LateUpdate(float dt)
{
	if (moveDistance >= range)
	{
		OnDie();
	}
}

void ObjectBullet::Draw(sf::RenderTexture& window)
{
	SpriteGo::Draw(window);
}

void ObjectBullet::CreateInit(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	Init();
	Reset();
	prePosition = pos;
	SetPosition(pos);
	SetDirection(direction);
	SetRotation(Utils::Angle360(direction));
	Flip();
	this->scene = scene;
	scene->AddGo(this);
	OnCreate();
}

void ObjectBullet::SetDirection(Direction direction)
{
	this->SetDirection(Utils::DirectionConversion(direction), true);
}

void ObjectBullet::SetDirection(const sf::Vector2f& direction, bool isConversed)
{
	this->direction = direction;
	if (!isConversed)
	{
		Utils::Normalize(this->direction);
	}
}

void ObjectBullet::Flip()
{

	if (direction.x != 0.f)
	{
		SetScale({ 1.f, abs(direction.x) / direction.x });
	}
}

void ObjectBullet::Homing(float dt)
{
	SetRotation(rotation + rotateSpeed * dt * Utils::AngleDirection(direction, targetPosition - position));
	SetDirection(sf::Transform().rotate(rotation).transformPoint(1.f, 0.f), true);

}

void ObjectBullet::OnCreate()
{
}

void ObjectBullet::OnDie()
{
	scene->RemoveGo(this);
}

void ObjectBullet::SetPosition(const sf::Vector2f& position)
{
	SpriteGo::SetPosition(position);
	bound.setPosition(position);

	moveDistance += Utils::Distance(prePosition, position);
	prePosition = position;

}

void ObjectBullet::SetTargetPosition(const sf::Vector2f position)
{
	targetPosition = position;
}
