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
	worldView.setSize(1280.f / 1.1f, 720.f / 1.1f);
	worldView.setCenter({ 0,-250 });
	uiView.setSize(1280.f / 1.1f, 720.f / 1.1f);
	uiView.setCenter(centerPos);

	auto bossPotato = new BossPotato("Boss");
	bossPotato->SetPosition({ 300.f, 0.f });
	AddGo(bossPotato);
	AddMonster(bossPotato);
	
	AddGo(new Player());

	Scene::Init();
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
	MonsterList.erase(std::remove_if(MonsterList.begin(), MonsterList.end(), [](ObjectMonster* monster) { return !monster->IsAlive(); }), MonsterList.end());
}

void SceneGame::Draw(sf::RenderTexture& window)
{
	Scene::Draw(window);
}

void SceneGame::AddMonster(ObjectMonster* monster)
{
	MonsterList.push_back(monster);
}

std::vector<ObjectMonster*> SceneGame::getAllMonsters() const
{
	return MonsterList;
}
