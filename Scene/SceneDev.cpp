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
	worldView.setSize(1280.f/1.1f,720.f/1.1f);
	worldView.setCenter(0.f, -250.f);

	//TODO 보스 테스트코드 삭제해야함
	//AddGo(new BossPotato())->SetPosition({500.f, 300.f});
	//AddGo(new BossOnion())->SetPosition({0, 300.f});
	//AddGo(new BossCarrot())->SetPosition({-500, 300.f});
	AddGo(new Stage01());
	AddGo(new Player());

	bgm.openFromFile("resource/Sprite/stage01/bgm_level_veggies.wav");
	bgm.setLoop(true);
	Scene::Init();
}

void SceneDev::Release()
{
	bgm.stop();
	Scene::Release();
}

void SceneDev::Enter()
{
	Scene::Enter();
	bgm.play();
}

void SceneDev::Exit()
{
	Scene::Exit();
}

void SceneDev::Draw(sf::RenderTexture& window)
{
	window.setView(worldView);
	sf::Sprite bg;
	bg.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0012.png"));
	Utils::SetOrigin(bg, Origins::MC);
	bg.setScale(2.0f, 2.0f);
	window.draw(bg);
	sf::Sprite bg2;
	bg2.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0003.png"));
	bg2.setScale(1.5f, 1.5f);
	Utils::SetOrigin(bg2, Origins::BC);
	bg2.setPosition(0.f, 450.f);
	window.draw(bg2);

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
