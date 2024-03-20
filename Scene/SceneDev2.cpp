#include "pch.h"
#include "SceneDev2.h"
#include "Player.h"

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
	worldView.setCenter({0,0});
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	AddGo(new Player());


	circle.setRadius(50.f);
	circle.setFillColor(sf::Color::Red);
	circle.setPosition({ centerPos.x, centerPos.y - 300});

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

void SceneDev2::Draw(sf::RenderWindow& window)
{
	window.draw(circle);
	Scene::Draw(window);
}
