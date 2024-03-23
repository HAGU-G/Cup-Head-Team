#include "pch.h"
#include "SceneTitle.h"
#include "Stage/Stage01.h"
#include "SpriteGo.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	worldView.setSize(sf::Vector2f(FRAMEWORK.GetWindowSize()));
	uiView.setSize(sf::Vector2f(FRAMEWORK.GetWindowSize()));
	bg = new SpriteGo("Background");
	bg->SetTexture("resource/Menu/cuphead_secondary_title_screen.png");
	float scale = std::max(worldView.getSize().x/bg->GetSize().x, worldView.getSize().y / bg->GetSize().y);
	bg->SetScale({ scale, scale });
	bg->SetOrigin(Origins::MC);
	bg->SetPosition(worldView.getCenter());
	AddGo(bg);
	Scene::Init();
}

void SceneTitle::Release()
{
	bgm.stop();
	Scene::Release();
}

void SceneTitle::Enter()
{
	Scene::Enter();
	bgm.stop();
	bgm.openFromFile("resource/Menu/MUS_Intro_DontDealWithDevil_Vocal.wav");
	bgm.play();
}

void SceneTitle::Exit()
{
	bgm.stop();
	Scene::Exit();
}

void SceneTitle::Draw(sf::RenderTexture& window)
{
	Scene::Draw(window);
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (bgm.getStatus() == sf::Sound::Status::Stopped)
	{
		bgm.openFromFile("resource/Menu/MUS_Intro_DontDealWithDevil.wav");
		bgm.setLoop(true);
		bgm.play();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		selectButton++;
		if (selectButton > 3)
		{
			selectButton = 1;
		}
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		selectButton--;
		if (selectButton < 1)
		{
			selectButton = 3;
		}
	}











	if (selectNum <= 0) { return; }
	switch (selectNum)
	{
	case 1:
	{
		Stage01* stage01 = new Stage01();
		stage01->Init();
		SCENE_MGR.GetScene(SceneIds::SceneGame)->AddGo(stage01);
	}
	break;
	case 2:
	{
		//SceneGame에서 사용할 오브젝트들 넣어주세요
	}
	break;
	case 3:
	{
		//SceneGame에서 사용할 오브젝트들 넣어주세요
	}
	break;
	default:
		break;
	}

	SCENE_MGR.ChangeScene(SceneIds::SceneGame);

}

void SceneTitle::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}
