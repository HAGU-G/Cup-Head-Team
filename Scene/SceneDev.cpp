#include "pch.h"
#include "SceneDev.h"
#include "Bullet/BulletPeaShot.h"
#include "Player.h"
#include "Stage/Stage01.h"

SceneDev::SceneDev(SceneIds id)
	:Scene(id)
{
}

SceneDev::~SceneDev()
{
}

void SceneDev::Init()
{
	worldView.setSize(FRAMEWORK.GetStageViewSize());
	worldView.setCenter(FRAMEWORK.GetStageViewCenter());

	//TODO 보스 테스트코드 삭제해야함
	//AddGo(new BossPotato())->SetPosition({500.f, 300.f});
	//AddGo(new BossOnion())->SetPosition({0, 300.f});
	//AddGo(new BossCarrot())->SetPosition({-500, 300.f});
	
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

void SceneDev::Draw(sf::RenderTexture& window)
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
			//BulletPeashot::Create(worldView.getCenter(), Direction::RightDown, this);
		}
		else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
		{
			//BulletPeashot::Create(worldView.getCenter(), Direction::RightUp, this);
		}
		else
		{
			//BulletPeashot::Create(worldView.getCenter(), Direction::Right, this);
		}
	}
	else if (InputMgr::GetAxisRaw(Axis::Horizontal) < 0.f)
	{
		if (InputMgr::GetAxisRaw(Axis::Vertical) > 0.f)
		{
			//BulletPeashot::Create(worldView.getCenter(), Direction::LeftDown, this);
		}
		else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
		{
			//BulletPeashot::Create(worldView.getCenter(), Direction::LeftUp, this);
		}
		else
		{
			//BulletPeashot::Create(worldView.getCenter(), Direction::Left, this);
		}
	}
	else if (InputMgr::GetAxisRaw(Axis::Vertical) < 0.f)
	{
		//BulletPeashot::Create(worldView.getCenter(), Direction::Up, this);
	}
	else if (InputMgr::GetAxisRaw(Axis::Vertical) > 0.f)
	{
		//BulletPeashot::Create(worldView.getCenter(), Direction::Down, this);
	}

}

void SceneDev::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);

}
