#include "pch.h"
#include "Stage02.h"
#include "Monster/BossRibby.h"
#include "Monster/BossCroaks.h"
#include "Player.h"
#include "SceneGame.h"
#include "Effect/EffectStage2BgGirls.h"
#include "Effect/EffectStage2BgWaiter.h"

Stage02::Stage02(const std::string& name)
	:GameObject(name)
{
}

void Stage02::Init()
{
	GameObject::Init();

    RES_MGR_TEXTURE.Load("resource/RibbyDeath.png");
    RES_MGR_TEXTURE.Load("resource/RibbyIdle.png");
    RES_MGR_TEXTURE.Load("resource/RibbyIntro.png");
    RES_MGR_TEXTURE.Load("resource/RibbyIntro2.png");
    RES_MGR_TEXTURE.Load("resource/RibbyRoll.png");
    RES_MGR_TEXTURE.Load("resource/RibbyRolling.png");
    RES_MGR_TEXTURE.Load("resource/RibbyShoot.png");
    RES_MGR_TEXTURE.Load("resource/RibbyShooting.png");
    RES_MGR_TEXTURE.Load("resource/RibbyShootEnd.png");
    RES_MGR_TEXTURE.Load("resource/RibbyBall.png");

	RES_MGR_TEXTURE.Load("resource/CroaksIdle.png");
	RES_MGR_TEXTURE.Load("resource/CroaksIntro.png");
	RES_MGR_TEXTURE.Load("resource/CroaksShoot.png");
	RES_MGR_TEXTURE.Load("resource/CroaksFanIntro.png");
	RES_MGR_TEXTURE.Load("resource/CroaksFanLoop.png");
	RES_MGR_TEXTURE.Load("resource/CroaksFanOutro.png");


	viewSize = FRAMEWORK.GetStageViewSize();


	scene = SCENE_MGR.GetScene(SceneIds::SceneGame);
	sceneGame = dynamic_cast<SceneGame*>(scene);

	EffectStage2BgGirls::Create({ viewSize.x * 0.1f / 3,-viewSize.y * 0.7f/2 }, { 1.f,0.f }, scene);
	EffectStage2BgWaiter::Create({ viewSize.x * 0.1f ,-viewSize.y * 0.4f / 2 }, { 1.f,0.f }, scene);
	SetBackground();
}

void Stage02::Update(float dt)
{
	GameObject::Update(dt);
	int currentHp = std::min(croaks->GetHp(), ribby->GetHp());
	croaks->SetHp(currentHp);
	ribby->SetHp(currentHp);
	if (!isVictory && currentHp == 0)
	{
		isVictory = true;
		sceneGame->SetStatus(SceneGame::Status::Victory);
	}
}

void Stage02::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void Stage02::Reset()
{
	croaks = new BossCroaks();
	ribby = new BossRibby();
	player = new Player("Player");

	croaks->sortLayer = 0;
	ribby->sortLayer = 1;
	player->sortLayer = 2;

	sceneGame->AddMonster(croaks);
	sceneGame->AddMonster(ribby);

	scene->AddGo(croaks);
	scene->AddGo(ribby);
	scene->AddGo(player);

	//croaks->Init();
	//ribby->Init();
	player->Init();

	//croaks->Reset();
	//ribby->Reset();
	player->Reset();

	//croaks->SetPosition({300.f, 0.f });
	//ribby->SetPosition({300.f, 0.f});
	player->SetPosition({ -300.f, 0.f });

	bg1->SetPosition({ 0.f, -viewSize.y * 0.43f });
	bg2->SetPosition({ 0.f, -viewSize.y * 0.48f });
	bg3->SetPosition({ 0.f, -viewSize.y * 0.38f });
	bg4->SetPosition({ 0.f, 50.f });
	bg5->SetPosition({ 0.f, 70.f });
}

void Stage02::Release()
{
	GameObject::Release();
}

void Stage02::Draw(sf::RenderTexture& window)
{
	GameObject::Draw(window);
}

void Stage02::SetBackground()
{
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

	bg1->SetPosition({ 0,-170 });
	bg2->SetPosition({ 0,-120 });
	bg3->SetPosition({ 0,80 });
	bg4->SetPosition({ 0,130 });
	bg5->SetPosition({ 0,170 });

	backgrounds.push_back(bg1);
	backgrounds.push_back(bg2);
	backgrounds.push_back(bg3);
	backgrounds.push_back(bg4);
	backgrounds.push_back(bg5);

	for (auto bg : backgrounds)
	{
		bg->SetOrigin(Origins::MC);
		bg->SetScale({ 1.3f, 1.3f });
	}

	bg1->sortLayer = -3;
	bg2->sortLayer = -2;
	bg3->sortLayer = -1;
	bg4->sortLayer = 3;
	bg5->sortLayer = 4;
	
	for (auto bg : backgrounds)
	{
		scene->AddGo(bg);
	}

}
