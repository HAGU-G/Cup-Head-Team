#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "Monster/BossPotato.h"
#include "Monster/BossOnion.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0,-300 });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	auto bossPotato = new BossPotato();
	bossPotato->SetPosition({ 300.f, 0.f });
	AddGo(bossPotato);
	BossList.push_back(bossPotato);

	AddGo(new Player());
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	BossList.erase(std::remove_if(BossList.begin(), BossList.end(), [](ObjectMonster* monster) { return !monster->IsAlive(); }), BossList.end());
}

void SceneGame::Draw(sf::RenderTexture& window)
{
	Scene::Draw(window);
}

std::vector<ObjectMonster*> SceneGame::getAllMonsters() const
{
	return BossList;
}
