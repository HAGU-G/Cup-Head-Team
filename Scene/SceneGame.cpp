#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "Stage/Stage01.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	worldView.setSize(FRAMEWORK.GetStageViewSize());
	worldView.setCenter(FRAMEWORK.GetStageViewCenter());
	
	AddGo(new Stage01());

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

void SceneGame::Victory()
{
}
