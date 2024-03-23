#include "pch.h"
#include "SceneDev2.h"
#include "Player.h"
#include "Monster/BossPotato.h"
#include "Monster/BossCarnation.h"

SceneDev2::SceneDev2(SceneIds id)
	:Scene(id)
{
}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Init()
{
	worldView.setSize(FRAMEWORK.GetStageViewSize());
	worldView.setCenter(FRAMEWORK.GetStageViewCenter());

	AddGo(new BossCarnation("bossCarnation"))->SetPosition({ 390.f,80.f });
	player = new Player();
	AddGo(player);

	Scene::Init();
}

void SceneDev2::Release()
{
	Scene::Release();
}

void SceneDev2::Enter()
{
	Scene::Enter();
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

}

void SceneDev2::Draw(sf::RenderTexture& window)
{
	window.draw(circle);
	Scene::Draw(window);
}
