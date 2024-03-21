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
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({0,-300.f});
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	background = new SpriteGo();
	background->SetTexture("resource/flower_bg_main.png");
	background->SetOrigin(Origins::MC);
	background->SetPosition({ 0,-300.f });
	AddGo(background);

	AddGo(new Player())->SetPosition({ 0.f,300.f });

	AddGo(new BossCarnation("bossCarnation"))->SetPosition({ 550.f,50.f });
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
