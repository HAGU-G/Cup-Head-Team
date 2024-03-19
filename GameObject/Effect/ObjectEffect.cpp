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
	this->scene = scene;
	scene->AddGo(this);
}

ObjectEffect* ObjectEffect::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	ObjectEffect* oe = new ObjectEffect();
	oe->CreateInit(pos, direction, scene);
	oe->isDieByTime = true;
	oe->duration = 0.5f;
	return oe;
}

void ObjectEffect::Init()
{
	SetTexture("resource/Sprite/peashot/weapon_peashot_death_0001.png");
	SetOrigin(Origins::MC);
}

void ObjectEffect::Update(float dt)
{
	if (isDieByTime) { deadTimer += dt; }
}

void ObjectEffect::LateUpdate(float dt)
{
	if (isDieByTime && deadTimer >= duration)
	{
		scene->RemoveGo(this);
	}
}

void ObjectEffect::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void ObjectEffect::SetDirection(const sf::Vector2f direction)
{
	this->direction = direction;
}
