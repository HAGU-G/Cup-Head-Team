#include "pch.h"
#include "SceneTest001.h"

SceneTest001::SceneTest001(const std::string& name)
	:Scene(name)
{
}

SceneTest001::~SceneTest001()
{
}

void SceneTest001::AddResource()
{
	//SFGM_TEXTURE.Add("sdfsdfsd");
}

void SceneTest001::Init()
{


	Scene::Init();
}

void SceneTest001::PreUpdate(float timeDelta, float timeScale)
{
	Scene::PreUpdate(timeDelta, timeScale);
}

void SceneTest001::Update(float timeDelta, float timeScale)
{
	Scene::Update(timeDelta, timeScale);
}

void SceneTest001::PostUpdate(float timeDelta, float timeScale)
{
	Scene::PostUpdate(timeDelta, timeScale);
}

void SceneTest001::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneTest001::Reset()
{
	Scene::Reset();
}

void SceneTest001::Release()
{
	Scene::Release();
}
