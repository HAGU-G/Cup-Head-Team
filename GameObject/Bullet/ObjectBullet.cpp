#include "pch.h"
#include "ObjectBullet.h"

ObjectBullet::ObjectBullet(const std::string& name)
	:ObjectMonster(name)
{
}

ObjectBullet::~ObjectBullet()
{
	OnDie();
}

void ObjectBullet::Init()
{
	animator.SetTarget(&sprite);
	if (owner == Owner::Enemy)
	{
		SetTarget(scene->FindGo("Player"));
	}
	hasHitBox = true;
	ObjectMonster::Init();
}

void ObjectBullet::Release()
{
	ObjectMonster::Release();
}

void ObjectBullet::Reset()
{
	ObjectMonster::Reset();

}

void ObjectBullet::Update(float dt)
{
	ObjectMonster::Update(dt);
	Translate(direction * speed * dt);
	if (type == Type::Homing)
	{
		if (!target) { doHoming = false; }
		else { SetTargetPosition(target->GetPosition()); }

		if (doHoming) { Homing(dt); }
		Flip();
	}
}

void ObjectBullet::LateUpdate(float dt)
{
	ObjectMonster::LateUpdate(dt);
	if (moveDistance >= range || position.y > 0.f || hp <= 0)
	{
		if (isAlive)
		{
			isAlive = false;
		}
		else
		{
			OnDie();
		}
	}
}

void ObjectBullet::Draw(sf::RenderTexture& window)
{
	ObjectMonster::Draw(window);
}

void ObjectBullet::CreateInit(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	this->scene = scene;
	Init();
	Reset();
	prePosition = pos;
	SetPosition(pos);
	SetDirection(direction);
	SetRotation(Utils::Angle360(direction));
	Flip();
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

sf::FloatRect ObjectBullet::GetCustomBounds() const
{
	return customBounds;
}

void ObjectBullet::SetPosition(const sf::Vector2f& position)
{
	ObjectMonster::SetPosition(position);
	bound.setPosition(position);

	moveDistance += Utils::Distance(prePosition, position);
	prePosition = position;

}

void ObjectBullet::SetTargetPosition(const sf::Vector2f position)
{
	targetPosition = position;
}

void ObjectBullet::SetTarget(GameObject* targetPtr)
{
	target = targetPtr;
}
