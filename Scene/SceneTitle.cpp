#include "pch.h"
#include "SceneTitle.h"
#include "Stage/Stage01.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	Scene::Init();
}

void SceneTitle::Release()
{
	Scene::Release();
}

void SceneTitle::Enter()
{
	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Draw(sf::RenderTexture& window)
{
	Scene::Draw(window);
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyUp(sf::Keyboard::Num1))
	{
		selectNum = 1;
	}
	else if (InputMgr::GetKeyUp(sf::Keyboard::Num2))
	{
		selectNum = 2;
	}
	else if (InputMgr::GetKeyUp(sf::Keyboard::Num3))
	{
		selectNum = 3;
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
