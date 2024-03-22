#include "pch.h"
#include "ObjectEffect.h"

ObjectEffect::ObjectEffect(const std::string& name)
	:SpriteGo(name)
{
}

void ObjectEffect::CreateInit(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	Init();
	Reset();
	SetPosition(pos);
	SetDirection(direction);
	SetRotation(Utils::Angle360(direction));
	if (direction.x < 0)
	{
		SetScale({ 1.f, -1.f });
	}
	this->scene = scene;
	scene->AddGo(this);
}

void ObjectEffect::Init()
{
	animator.SetTarget(&sprite);
}

void ObjectEffect::Update(float dt)
{
	SpriteGo::Update(dt);
	if (isDieByTime) { deadTimer += dt; }
}

void ObjectEffect::LateUpdate(float dt)
{
	if (isDieByTime && deadTimer >= duration)
	{
		OnDie();
	}
}

void ObjectEffect::Draw(sf::RenderTexture& window)
{
	SpriteGo::Draw(window);
}

void ObjectEffect::SetDirection(const sf::Vector2f direction)
{
	this->direction = direction;
}

void ObjectEffect::OnDie()
{
	scene->RemoveGo(this);
}
