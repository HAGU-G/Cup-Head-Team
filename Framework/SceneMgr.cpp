#include "pch.h"
#include "SceneMgr.h"
#include "SceneDev2.h"


SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Init()
{
	Release(); 
	//scenes.push_back(new SceneTitle(SceneIds::SceneTitle));
	//scenes.push_back(new SceneIntro(SceneIds::SceneIntro));
	//scenes.push_back(new SceneMapTool(SceneIds::SceneMapTool));
	//scenes.push_back(new SceneDev1(SceneIds::SceneDev1));
	scenes.push_back(new SceneDev2(SceneIds::SceneDev2));
	
	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentScene = startScene;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	// TO-DO: 모든 게임 오브젝트 업데이트 끝난 후에 씬 전환 되도록

	nextScene = id;

}

bool SceneMgr::Update(float dt)
{
	if (InputMgr::GetKey(sf::Keyboard::P) && InputMgr::GetKeyDown(sf::Keyboard::O))
	{
		isDeveloperMode = !isDeveloperMode;
	}

	scenes[(int)currentScene]->Update(dt);

	if (nextScene != SceneIds::None)
	{
		scenes[(int)currentScene]->Exit();
		currentScene = nextScene;
		scenes[(int)currentScene]->Enter();

		nextScene = SceneIds::None;
		return false;
	}
	return true;
 }

void SceneMgr::LateUpdate(float dt)
{
	scenes[(int)currentScene]->LateUpdate(dt);
}

void SceneMgr::FixedUpdate(float dt)
{
	scenes[(int)currentScene]->FixedUpdate(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->Draw(window);
}
