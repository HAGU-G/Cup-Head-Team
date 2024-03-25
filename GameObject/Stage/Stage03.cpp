#include "pch.h"
#include "Stage03.h"
#include "SceneGame.h"
#include "Player.h"
#include "Monster/BossCarnation.h"

Stage03::Stage03(const std::string& name)
	:GameObject(name)
{
}

void Stage03::Init()
{
	RES_MGR_TEXTURE.Load("resource/carnationBossIntro.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossIdle.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossFa_High.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossFa_Low.png");
	RES_MGR_TEXTURE.Load("resource/carntionBossFireSeed.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossFinalIntro.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossFinalIdle.png");
	RES_MGR_TEXTURE.Load("resource/carnationBossDie.png");

	mainBg = new SpriteGo("mainBg");
	mainBg->SetTexture("resource/Sprite/stage02/flower_bg_main1.png");
	mainBg->SetPosition({ 0.f,140.f });
	mainBg->SetOrigin(Origins::BC);
	mainBg->sortLayer = -1;
	mainBg->SetScale({ 0.8f,0.8f });

	skyBg = new SpriteGo("skyBg");
	skyBg->SetTexture("resource/Sprite/stage02/flower_bg_sky.png");
	skyBg->SetPosition({ 0.f,-190.f });
	skyBg->SetOrigin(Origins::BC);
	skyBg->sortLayer = -2;
	skyBg->SetScale({ 0.8f,0.8f });

	cloudBg = new SpriteGo("cloudBg");
	cloudBg->SetTexture("resource/Sprite/stage02/flower_bg_clouds_b.png");
	cloudBg->SetPosition({ 0.f,-190.f });
	cloudBg->SetOrigin(Origins::BC);
	cloudBg->sortLayer = -2;
	cloudBg->SetScale({ 0.8f,0.8f });

	frontCloudBg = new SpriteGo("frontCloudBg");
	frontCloudBg->SetTexture("resource/Sprite/stage02/flower_bg_clouds_a.png");
	frontCloudBg->SetPosition({ 0.f,-190.f });
	frontCloudBg->SetOrigin(Origins::BC);
	frontCloudBg->sortLayer = -2;
	frontCloudBg->SetScale({ 0.8f,0.8f });

	cloudBg2 = new SpriteGo("cloudBg2");
	cloudBg2->SetTexture("resource/Sprite/stage02/flower_bg_clouds_b.png");
	cloudBg2->SetPosition({ cloudBg->GetGlobalBounds().width,-190.f });
	cloudBg2->SetOrigin(Origins::BC);
	cloudBg2->sortLayer = -2;
	cloudBg2->SetScale({ 0.8f,0.8f });

	frontCloudBg2 = new SpriteGo("frontCloudBg2");
	frontCloudBg2->SetTexture("resource/Sprite/stage02/flower_bg_clouds_a.png");
	frontCloudBg2->SetPosition({ frontCloudBg->GetGlobalBounds().width,-190.f });
	frontCloudBg2->SetOrigin(Origins::BC);
	frontCloudBg2->sortLayer = -2;
	frontCloudBg2->SetScale({ 0.8f,0.8f });

	frontBush = new SpriteGo("frontBush");
	frontBush->SetTexture("resource/Sprite/stage02/flower_bg_fg-bush.png");
	frontBush->SetPosition({ 310.f,80.f });
	frontBush->SetOrigin(Origins::BL);
	frontBush->sortLayer = 1;
	frontBush->SetScale({ 0.8f,0.8f });

	frontBg = new SpriteGo("frontBg");
	frontBg->SetTexture("resource/Sprite/stage02/flower_bg_fg.png");
	frontBg->SetPosition({ 0.f,150.f });
	frontBg->SetOrigin(Origins::BC);
	frontBg->sortLayer = 2;
	frontBg->SetScale({ 0.8f,0.8f });

	viewSize = FRAMEWORK.GetStageViewSize();
	playerPosCorrection = sf::Vector2f(viewSize.x * 0.5f * 0.545f, 0.f);

	scene = SCENE_MGR.GetScene(SceneIds::SceneGame);
	sceneGame = dynamic_cast<SceneGame*>(scene);
}

void Stage03::Update(float dt)
{
	GameObject::Update(dt);
	sceneGame->AddMonster(carnation);

	sf::Vector2f cloudPos = cloudBg->GetPosition();
	sf::Vector2f cloudPos2 = cloudBg2->GetPosition();

	sf::Vector2f frontCloudPos = frontCloudBg->GetPosition();
	sf::Vector2f frontCloudPos2 = frontCloudBg2->GetPosition();

	cloudPos.x += cloudSpeed * dt;
	cloudPos2.x += cloudSpeed * dt;

	frontCloudPos.x += frontCloudSpeed * dt;
	frontCloudPos2.x += frontCloudSpeed * dt;

	if (cloudPos.x + cloudBg->GetGlobalBounds().width < 0)
	{
		cloudPos.x = cloudPos2.x + cloudBg->GetGlobalBounds().width;
	}
	else if (cloudPos2.x + cloudBg->GetGlobalBounds().width < 0)
	{
		cloudPos2.x = cloudPos.x + cloudBg->GetGlobalBounds().width;
	}

	if (frontCloudPos.x + frontCloudBg->GetGlobalBounds().width < 0)
	{
		frontCloudPos.x = frontCloudPos2.x + frontCloudBg->GetGlobalBounds().width;
	}
	else if (frontCloudPos2.x + frontCloudBg->GetGlobalBounds().width < 0)
	{
		frontCloudPos2.x = frontCloudPos.x + frontCloudBg->GetGlobalBounds().width;
	}

	cloudBg->SetPosition(cloudPos);
	cloudBg2->SetPosition(cloudPos2);

	frontCloudBg->SetPosition(frontCloudPos);
	frontCloudBg2->SetPosition(frontCloudPos2);

	carnationHp = carnation->GetHp();
}

void Stage03::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);

	if (player) { playerPos = player->GetPosition(); }
	else { playerPos = { 0.f, 0.f }; }

	if (player && playerPos.x >= -550.f && playerPos.x <= 0.f)
	{
		float viewX = (playerPos.x + playerPosCorrection.x) * 0.05f;
		float playerPosDeltaX = playerPos.x - playerPrePos.x;
		scene->GetWorldView().setCenter(viewX, scene->GetWorldView().getCenter().y);
	}
	playerPrePos = playerPos;
}

void Stage03::Reset()
{
	bgm.stop();
	if (player)
	{
		player->Release();
		scene->RemoveGo(player);
		player = nullptr;
	}
	if (carnation)
	{
		carnation->Release();
		scene->RemoveGo(carnation);
		carnation = nullptr;
	}


	player = new Player("Player");
	carnation = new	BossCarnation();

	carnation->sortLayer = 0;
	player->sortLayer = 1;

	player->Init();
	carnation->Init();

	player->Reset();
	carnation->Reset();

	carnationMaxHp = carnation->GetMaxHp();

	carnation->SetPosition({ viewSize.x * 0.5f * 0.663f, 100.f });
	player->SetPosition({ -playerPosCorrection.x, 0.f });
	playerPrePos = playerPos;

	scene->AddGo(mainBg);
	scene->AddGo(skyBg);
	scene->AddGo(cloudBg);
	scene->AddGo(frontCloudBg);
	scene->AddGo(cloudBg2);
	scene->AddGo(frontCloudBg2);
	scene->AddGo(frontBush);
	scene->AddGo(frontBg);

	scene->AddGo(player);
	sceneGame->AddGo(carnation);
}

void Stage03::Release()
{
	GameObject::Release();
}

void Stage03::Draw(sf::RenderTexture& window)
{
	GameObject::Draw(window);
}
