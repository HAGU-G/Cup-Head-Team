#include "pch.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "SceneDev1.h"
#include "SceneTitle.h"


SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Init()
{
	Release(); 
	scenes.push_back(new SceneGame(SceneIds::SceneGame));
	scenes.push_back(new SceneDev1(SceneIds::SceneDev1));
	scenes.push_back(new SceneTitle(SceneIds::SceneTitle));

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
	// TO-DO: ��� ���� ������Ʈ ������Ʈ ���� �Ŀ� �� ��ȯ �ǵ���

	nextScene = id;

}

Scene* SceneMgr::GetScene(SceneIds id)
{
	auto getScene = scenes.begin();
	while (getScene != scenes.end())
	{
		if ((*getScene)->GetId() == id)
		{
			return (*getScene);
		}
		else
		{
			getScene++;
		}
	}
	return nullptr;
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

void SceneMgr::Draw(sf::RenderTexture& window)
{
	scenes[(int)currentScene]->Draw(window);
	if (isDeveloperMode)
	{
		sf::Text text;
		text.setCharacterSize(50);
		text.setFillColor(sf::Color::Magenta);
		text.setFont(RES_MGR_FONT.Get("resource/Font/CupheadVogue-ExtraBold.ttf"));
		text.setString(std::to_string(int(1.f / FRAMEWORK.GetDT())));
		text.setPosition(GetCurrentScene()->GetUiView().getCenter() - GetCurrentScene()->GetUiView().getSize() * 0.5f);
		window.draw(text);
	}
}
