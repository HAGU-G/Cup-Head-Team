#include "pch.h"
#include "SceneDev.h"
#include "Bullet/ObjectBullet.h"

SceneDev::SceneDev(SceneIds id)
	:Scene(id)
{
}

SceneDev::~SceneDev()
{
}

void SceneDev::Init()
{
	worldView.setSize(sf::Vector2f(FRAMEWORK.GetWindowSize()));
	worldView.setCenter(960, 540);
	ObjectBullet* ob = new ObjectBullet();
	AddGo(ob);
	Scene::Init();
}

void SceneDev::Release()
{
	Scene::Release();
}

void SceneDev::Enter()
{
	Scene::Enter();
}

void SceneDev::Exit()
{
	Scene::Exit();
}

void SceneDev::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneDev::Update(float dt)
{
	Scene::Update(dt);


	if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		ObjectBullet::Create({ 960,540 }, Direction::Up, this);
	}
}
