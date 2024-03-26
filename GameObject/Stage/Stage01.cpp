#include "pch.h"
#include "Stage01.h"
#include "Monster/BossPotato.h"
#include "Monster/BossOnion.h"
#include "Monster/BossCarrot.h"
#include "Player.h"
#include "SceneGame.h"

Stage01::Stage01(const std::string& name)
	:GameObject(name)
{
}

void Stage01::Init()
{
	RES_MGR_TEXTURE.Load("resource/potatoDeath.png");
	RES_MGR_TEXTURE.Load("resource/potatoIdle.png");
	RES_MGR_TEXTURE.Load("resource/potatoIntro.png");
	RES_MGR_TEXTURE.Load("resource/potatoLeave.png");
	RES_MGR_TEXTURE.Load("resource/potatoShoot.png");

	RES_MGR_TEXTURE.Load("resource/onionDeath.png");
	RES_MGR_TEXTURE.Load("resource/onionIdle.png");
	RES_MGR_TEXTURE.Load("resource/onionIntro.png");
	RES_MGR_TEXTURE.Load("resource/onionLeave.png");
	RES_MGR_TEXTURE.Load("resource/onionCry.png");
	RES_MGR_TEXTURE.Load("resource/onionCrying.png");

	RES_MGR_TEXTURE.Load("resource/carrotDeath.png");
	RES_MGR_TEXTURE.Load("resource/carrotIdle.png");
	RES_MGR_TEXTURE.Load("resource/carrotIntro.png");
	RES_MGR_TEXTURE.Load("resource/carrotShootBody.png");
	RES_MGR_TEXTURE.Load("resource/carrotShootEyes.png");
	RES_MGR_TEXTURE.Load("resource/carrotRing.png");
	RES_MGR_TEXTURE.Load("resource/carrotBoom.png");
	RES_MGR_TEXTURE.Load("resource/carrotRingDeath.png");
	RES_MGR_TEXTURE.Load("resource/carrotBoomDeath.png");
	RES_MGR_TEXTURE.Load("resource/carrotRingIntro.png");

	viewSize = FRAMEWORK.GetStageViewSize();
	playerPosCorrection = sf::Vector2f(viewSize.x * 0.5f * 0.545f, 0.f);

	scene = SCENE_MGR.GetScene(SceneIds::SceneGame);
	sceneGame = dynamic_cast<SceneGame*>(scene);

	SetBackground();
}

void Stage01::Update(float dt)
{
	GameObject::Update(dt);
	if (swapping)
	{
		if (swapTimer >= swapTime)
		{
			swapping = false;
			swapTimer = 0.f;

			switch (phase)
			{
			case 2:
				onion->SetActive(true);
				sceneGame->AddMonster(onion);
				break;
			case 3:
				carrot->SetActive(true);
				sceneGame->AddMonster(carrot);
				break;
			default:
				break;
			}

		}
		{
			swapTimer += dt;
			return;
		}
	}

	switch (phase)
	{
	case 0:
		phase = 1;
		potato->SetActive(true);
		sceneGame->AddMonster(potato);
		break;
	case 1:
		if (potato->GetHp() <= 0)
		{
			phase = 2;
			swapping = true;
		}
		potatoHp = potato->GetHp();
		break;
	case 2:
		if (onion->GetHp() <= 0)
		{
			phase = 3;
			swapping = true;
		}
		onionHp = onion->GetHp();
		break;
	case 3:
		if (carrot->GetHp() <= 0)
		{
			sceneGame->SetStatus(SceneGame::Status::Victory);
			phase = -1;
		}
		carrotHp = carrot->GetHp();
		break;
	default:
		break;
	}
}

void Stage01::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);

	if (player) { playerPos = player->GetPosition(); }
	else { playerPos = { 0.f, 0.f }; }

	if (player && playerPos.x >= -550.f && playerPos.x <= 0.f)
	{
		float viewX = (playerPos.x + playerPosCorrection.x) * 0.05f;
		float playerPosDeltaX = playerPos.x - playerPrePos.x;
		scene->GetWorldView().setCenter(viewX, scene->GetWorldView().getCenter().y);
		frontFence->SetPosition(frontFence->GetPosition() + sf::Vector2f(playerPosDeltaX * -0.03f, 0.f));
		frontFlower->SetPosition(frontFlower->GetPosition() + sf::Vector2f(playerPosDeltaX * -0.03f, 0.f));
		int count = 0;
		for (auto ptr : backgrounds)
		{
			if (ptr == frontFence || ptr == frontFlower)
			{
				continue;
			}
			ptr->SetPosition(ptr->GetPosition() + sf::Vector2f(playerPosDeltaX * -(0.011f - 0.001 * count), 0.f));
			count++;
		}
	}
	playerPrePos = playerPos;

	if (player->GetHp() <= 0 && sceneGame->GetStatus() < SceneGame::Status::Defeat)
	{
		sceneGame->SetStatus(SceneGame::Status::Defeat);
	}
}

void Stage01::Reset()
{
	SOUND_MGR.StopBgm();
	if (player)
	{
		player->Release();
		scene->RemoveGo(player);
		player = nullptr;
	}

	if (potato)
	{
		potato->Release();
		scene->RemoveGo(potato);
		potato = nullptr;
	}
	if (onion)
	{
		onion->Release();
		scene->RemoveGo(onion);
		potato = nullptr;
	}
	if (carrot)
	{
		carrot->Release();
		scene->RemoveGo(carrot);
		potato = nullptr;
	}

	player = new Player("Player");
	potato = new BossPotato();
	onion = new BossOnion();
	carrot = new BossCarrot();

	potato->sortLayer = 0;
	onion->sortLayer = 0;
	player->sortLayer = 1;
	carrot->sortLayer = -3;

	scene->AddGo(player);
	scene->AddGo(potato);
	scene->AddGo(onion);
	scene->AddGo(carrot);
	potato->SetActive(false);
	onion->SetActive(false);
	carrot->SetActive(false);

	player->Init();
	potato->Init();
	onion->Init();
	carrot->Init();

	player->Reset();
	potato->Reset();
	onion->Reset();
	carrot->Reset();

	potato->SetPosition({ viewSize.x * 0.5f * 0.663f, 0.f });
	carrot->SetPosition({ 0.f , -viewSize.y * 0.10f });
	player->SetPosition({ -playerPosCorrection.x, 0.f });
	playerPrePos = playerPos;

	potatoHp = potato->GetMaxHp();
	onionHp = onion->GetMaxHp();
	carrotHp = carrot->GetMaxHp();
	totalMaxHp = potatoHp + onionHp + carrotHp;

	frontFence->SetPosition({ -viewSize.x * 0.37f, 0.f });
	frontFlower->SetPosition({ viewSize.x * 0.32f, viewSize.y * 0.025f });
	ground->SetPosition({ 0.f, -viewSize.y * 0.08f });
	field4->SetPosition({ 0.f, -viewSize.y * 0.23f });
	field5->SetPosition({ 0.f, -viewSize.y * 0.28f });
	field6->SetPosition({ 0.f, -viewSize.y * 0.31f });
	field7->SetPosition({ 0.f, -viewSize.y * 0.34f });
	field8->SetPosition({ 0.f, -viewSize.y * 0.37f });
	field9->SetPosition({ 0.f, -viewSize.y * 0.345f });
	field10->SetPosition({ 0.f, -viewSize.y * 0.615f });
	field11->SetPosition({ 0.f, -viewSize.y * 0.43f });
	sky->SetPosition({ 0.f, -viewSize.y * 0.50f });

	SOUND_MGR.PlayBgm("resource/Sprite/stage01/bgm_level_veggies.wav",false);
}

void Stage01::Release()
{
	SOUND_MGR.StopBgm();
	GameObject::Release();
}

void Stage01::Draw(sf::RenderTexture& window)
{
	GameObject::Draw(window);
}

void Stage01::SetBackground()
{
	frontFence = new SpriteGo();
	frontFlower = new SpriteGo();
	ground = new SpriteGo();
	field4 = new SpriteGo();
	field5 = new SpriteGo();
	field6 = new SpriteGo();
	field7 = new SpriteGo();
	field8 = new SpriteGo();
	field9 = new SpriteGo();
	field10 = new SpriteGo();
	field11 = new SpriteGo();
	sky = new SpriteGo();

	frontFence->SetTexture("resource/Sprite/stage01/veggie_bg_0002.png");
	frontFlower->SetTexture("resource/Sprite/stage01/veggie_bg_0001.png");
	ground->SetTexture("resource/Sprite/stage01/veggie_bg_0003.png");
	field4->SetTexture("resource/Sprite/stage01/veggie_bg_0004.png");
	field5->SetTexture("resource/Sprite/stage01/veggie_bg_0005.png");
	field6->SetTexture("resource/Sprite/stage01/veggie_bg_0006.png");
	field7->SetTexture("resource/Sprite/stage01/veggie_bg_0007.png");
	field8->SetTexture("resource/Sprite/stage01/veggie_bg_0008.png");
	field9->SetTexture("resource/Sprite/stage01/veggie_bg_0009.png");
	field10->SetTexture("resource/Sprite/stage01/veggie_bg_0010.png");
	field11->SetTexture("resource/Sprite/stage01/veggie_bg_0011.png");
	sky->SetTexture("resource/Sprite/stage01/veggie_bg_0012.png");

	backgrounds.push_back(frontFence);
	backgrounds.push_back(frontFlower);
	backgrounds.push_back(ground);
	backgrounds.push_back(field4);
	backgrounds.push_back(field5);
	backgrounds.push_back(field6);
	backgrounds.push_back(field7);
	backgrounds.push_back(field8);
	backgrounds.push_back(field9);
	backgrounds.push_back(field10);
	backgrounds.push_back(field11);
	backgrounds.push_back(sky);

	for (auto ptr : backgrounds)
	{
		ptr->SetOrigin(Origins::MC);
		ptr->SetScale({ 1.3f, 1.3f });
	}

	frontFence->sortLayer = 2;
	frontFlower->sortLayer = 2;
	ground->sortLayer = -1;
	field4->sortLayer = -2;
	field5->sortLayer = -4;
	field6->sortLayer = -5;
	field7->sortLayer = -6;
	field8->sortLayer = -7;
	field9->sortLayer = -8;
	field10->sortLayer = -9;
	field11->sortLayer = -10;
	sky->sortLayer = -11;

	for (auto ptr : backgrounds)
	{
		scene->AddGo(ptr);
	}

	//TODO Å¸ÀÌ¾î

}
