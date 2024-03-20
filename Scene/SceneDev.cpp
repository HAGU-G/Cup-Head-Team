#include "pch.h"
#include "SceneDev.h"
#include "Bullet/BulletPeaShot.h"

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
	worldView.setCenter(0.f, 0.f);
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


	if (InputMgr::GetAxisRaw(Axis::Horizontal) > 0.f)
	{
		if (InputMgr::GetAxisRaw(Axis::Vertical) > 0.f)
		{
			BulletPeashot::Create(worldView.getCenter(), Direction::RightDown, this);
		}
		else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
		{
			BulletPeashot::Create(worldView.getCenter(), Direction::RightUp, this);
		}
		else
		{
			BulletPeashot::Create(worldView.getCenter(), Direction::Right, this);
		}
	}
	else if (InputMgr::GetAxisRaw(Axis::Horizontal) < 0.f)
	{
		if (InputMgr::GetAxisRaw(Axis::Vertical) > 0.f)
		{
			BulletPeashot::Create(worldView.getCenter(), Direction::LeftDown, this);
		}
		else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
		{
			BulletPeashot::Create(worldView.getCenter(), Direction::LeftUp, this);
		}
		else
		{
			BulletPeashot::Create(worldView.getCenter(), Direction::Left, this);
		}
	}
	else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
	{
		BulletPeashot::Create(worldView.getCenter(), Direction::Up, this);
	}
	else if (InputMgr::GetAxisRaw(Axis::Vertical) > 0.f)
	{
		BulletPeashot::Create(worldView.getCenter(), Direction::Down, this);
	}

}
