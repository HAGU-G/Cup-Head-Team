#include "pch.h"
#include "SceneTitle.h"
#include "Stage/Stage01.h"
#include "SpriteGo.h"
#include "UI/ObjectButton.h"

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

	//�������
	bgm.setVolume(50.f);

	//���
	bg = new SpriteGo("Background");
	bg->SetTexture("resource/Menu/cuphead_secondary_title_screen.png");
	float scale = std::max(worldView.getSize().x / bg->GetSize().x, worldView.getSize().y / bg->GetSize().y);
	bg->SetScale({ scale, scale });
	bg->SetOrigin(Origins::MC);
	bg->SetPosition(worldView.getCenter());
	AddGo(bg);

	//��ư
	start = new ObjectButton("Start");
	option = new ObjectButton("Option");
	exit = new ObjectButton("Exit");

	start->SetOrigin(Origins::BC);
	option->SetOrigin(Origins::BC);
	exit->SetOrigin(Origins::BC);

	start->SetString(L"����");
	option->SetString(L"�ɼ�");
	exit->SetString(L"����");

	start->SetFunction([this]() {
		SCENE_MGR.ChangeScene(SceneIds::SceneGame);
		return start;
		});
	option->SetFunction([this]() {
		return option;
		});
	exit->SetFunction([this]() {
		FRAMEWORK.GetWindowReal().close();
		return exit;
		});

	sf::Vector2f buttonPosY = { 0.f, float(-fontSize * 3) };
	start->SetPosition(uiView.getCenter() + buttonPosY);
	buttonPosY.y += fontSize;
	option->SetPosition(uiView.getCenter() + buttonPosY);
	buttonPosY.y += fontSize;
	exit->SetPosition(uiView.getCenter() + buttonPosY);

	AddGo(start, Ui);
	AddGo(option, Ui);
	AddGo(exit, Ui);

	//Init
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

	start->Select();
	option->UnSelect();
	exit->UnSelect();

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

	//�������2 �ݺ����
	if (bgm.getStatus() == sf::Sound::Status::Stopped)
	{
		bgm.openFromFile("resource/Menu/MUS_Intro_DontDealWithDevil.wav");
		bgm.play();
	}

	//��ư ����
	if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		selectButton++;
		if (selectButton > 3)
		{
			selectButton = 1;
		}
		ButtonSelect();
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		selectButton--;
		if (selectButton < 1)
		{
			selectButton = 3;
		}
		ButtonSelect();
	}

	//��ư Ŭ��
	if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		ButtonPress();
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
		//SceneGame���� ����� ������Ʈ�� �־��ּ���
	}
	break;
	case 3:
	{
		//SceneGame���� ����� ������Ʈ�� �־��ּ���
	}
	break;
	default:
		break;
	}
	selectNum = -1;

}

void SceneTitle::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneTitle::ButtonSelect()
{
	switch (selectButton)
	{
	case 1:
		start->Select();
		option->UnSelect();
		exit->UnSelect();
		break;
	case 2:
		start->UnSelect();
		option->Select();
		exit->UnSelect();
		break;
	case 3:
		start->UnSelect();
		option->UnSelect();
		exit->Select();
		break;
	default:
		break;
	}
}

void SceneTitle::ButtonPress()
{
	switch (selectButton)
	{
	case 1:
		start->Press();
		break;
	case 2:
		option->Press();
		break;
	case 3:
		exit->Press();
		break;
	default:
		break;
	}
}
