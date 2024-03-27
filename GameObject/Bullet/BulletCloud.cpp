#include "pch.h"
#include "BulletCloud.h"
#include "SceneGame.h"

BulletCloud::BulletCloud(const std::string& name)
	:ObjectBullet(name)
{
}

BulletCloud* BulletCloud::Create(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene)
{
	BulletCloud* bc = new BulletCloud();
	bc->sortLayer = -11;
	bc->CreateInit(pos, direction, scene);
	bc->SetRotation(0.f);
	bc->SetScale({ 1.f, 1.f });
	return bc;
}

void BulletCloud::Update(float dt)
{
	ObjectBullet::Update(dt);
	if (position.x < scene->GetWorldView().getCenter().x - scene->GetWorldView().getSize().x - sprite.getGlobalBounds().width)
	{
		SetPosition({ scene->GetWorldView().getCenter().x + scene->GetWorldView().getSize().x , position.y });
	}
}

void BulletCloud::LateUpdate(float dt)
{

}
