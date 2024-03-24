#include "pch.h"
#include "SceneDev3.h"
#include "Player.h"
#include "Monster/BossRibby.h"
#include "Monster/BossCroaks.h"
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
	worldView.setSize(1280.f/1.1f,720.f/1.1f);
	worldView.setCenter({ 0,-250 });
	uiView.setSize(1280.f / 1.1f, 720.f / 1.1f);
	uiView.setCenter(centerPos);

	bg1 = new SpriteGo();
	bg2 = new SpriteGo();
	bg3 = new SpriteGo();
	bg4 = new SpriteGo();
	bg5 = new SpriteGo();

	bg1->SetTexture("resource/Sprite/stage03/jazzbar_bg_01.png");
	bg2->SetTexture("resource/Sprite/stage03/jazzbar_bg_02.png");
	bg3->SetTexture("resource/Sprite/stage03/jazzbar_bg_03.png");
	bg4->SetTexture("resource/Sprite/stage03/jazzbar_bg_04.png");
	bg5->SetTexture("resource/Sprite/stage03/jazzbar_bg_05.png");

	bg1->SetOrigin(Origins::BC);
	bg2->SetOrigin(Origins::BC);
	bg3->SetOrigin(Origins::BC);
	bg4->SetOrigin(Origins::BC);
	bg5->SetOrigin(Origins::BC);

	bg1->SetScale({ 1.3f, 1.3f });
	bg2->SetScale({ 1.3f, 1.3f });
	bg3->SetScale({ 1.3f, 1.3f });
	bg4->SetScale({ 1.3f, 1.3f });
	bg5->SetScale({ 1.3f, 1.3f });

	bg1->SetPosition({ 0,-170 });
	bg2->SetPosition({ 0,-120 });
	bg3->SetPosition({ 0,80 });
	bg4->SetPosition({ 0,130 });
	bg5->SetPosition({ 0,170 });

	AddGo(bg1);
	AddGo(bg2);
	AddGo(bg3);

	auto bossCroaks = new BossCroaks("Boss");
	bossCroaks->SetPosition({ 300.f, 0.f });
	AddGo(bossCroaks);
	
	auto bossRibby = new BossRibby("Boss");
	bossRibby->SetPosition({ 300.f, 0.f });
	AddGo(bossRibby);


	AddGo(new Player());
	AddGo(bg4);
	AddGo(bg5);

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