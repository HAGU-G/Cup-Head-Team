#include "pch.h"
#include "SceneDev3.h"
#include "Player.h"
#include "Monster/BossPotato.h"
#include "Monster/BossOnion.h"
#include "Bullet/BulletCarrotBoom.h"

SceneDev3::SceneDev3(SceneIds id)
	:Scene(id)
{
}

SceneDev3::~SceneDev3()
{
}

void SceneDev3::Init()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0,0 });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	auto bossOnion = new BossOnion("Boss");
	bossOnion->SetPosition({ -300.f, 0.f });
	AddGo(bossOnion);
	AddMonster(bossOnion);

	auto bossPotato = new BossPotato("Boss");
	bossPotato->SetPosition({ 300.f, 0.f });
	AddGo(bossPotato);
	AddMonster(bossPotato);

	AddGo(new Player());

	Scene::Init();

}

void SceneDev3::Release()
{
	Scene::Release();
}

void SceneDev3::Enter()
{
	Scene::Enter();
}

void SceneDev3::Exit()
{
	Scene::Exit();
}

void SceneDev3::Update(float dt)
{
	Scene::Update(dt);
	BossList.erase(std::remove_if(BossList.begin(), BossList.end(),[](ObjectMonster* monster) { return !monster->IsAlive(); }), BossList.end());


}

void SceneDev3::Draw(sf::RenderTexture& window)
{
	Scene::Draw(window);
}

void SceneDev3::AddMonster(ObjectMonster* monster)
{
	BossList.push_back(monster);
}

std::vector<ObjectMonster*> SceneDev3::getAllMonsters() const
{
	return BossList;
}