#include "pch.h"
#include "Stage01.h"
#include "Monster/BossPotato.h"
#include "Monster/BossOnion.h"
#include "Monster/BossCarrot.h"
#include "Player.h"

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


	frontFence.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0001.png"));
	frontFlower.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0002.png"));
	ground.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0003.png"));
	field4.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0004.png"));
	field5.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0005.png"));
	field6.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0006.png"));
	field7.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0007.png"));
	field8.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0008.png"));
	field9.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0009.png"));
	field10.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0010.png"));
	field11.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0011.png"));
	sky.setTexture(RES_MGR_TEXTURE.Get("resource/Sprite/stage01/veggie_bg_0012.png"));

	Utils::SetOrigin(frontFence, Origins::BC);
	Utils::SetOrigin(frontFlower, Origins::BC);
	Utils::SetOrigin(ground, Origins::BC);
	Utils::SetOrigin(field4, Origins::BC);
	Utils::SetOrigin(field5, Origins::BC);
	Utils::SetOrigin(field6, Origins::BC);
	Utils::SetOrigin(field7, Origins::BC);
	Utils::SetOrigin(field8, Origins::BC);
	Utils::SetOrigin(field9, Origins::BC);
	Utils::SetOrigin(field10, Origins::BC);
	Utils::SetOrigin(field11, Origins::BC);
	Utils::SetOrigin(sky, Origins::BC);




	bgm.openFromFile("resource/Sprite/stage01/bgm_level_veggies.wav");
	bgm.setLoop(true);
	viewSize = FRAMEWORK.GetStageViewSize();
	playerPosCorrection = sf::Vector2f(viewSize.x * 0.5f * 0.75f, 0.f);
}

void Stage01::Update(float dt)
{
	GameObject::Update(dt);
	switch (phase)
	{
	case 0:
		phase = 1;
		break;
	case 1:
		potato->Update(dt);
		if (potato->GetHp() <= 0)
		{
			phase = 2;
		}
		potatoHp = potato->GetHp();
		break;
	case 2:
		onion->Update(dt);
		if (onion->GetHp() <= 0)
		{
			phase = 3;
		}
		onionHp = onion->GetHp();
		break;
	case 3:
		carrot->Update(dt);
		if (carrot->GetHp() <= 0)
		{

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

	if (player)
	{
		float viewX = viewSize.x * 0.1f * (playerPos.x + playerPosCorrection.x) / (viewSize.x * 1.1f * 0.5f);
		scene->GetWorldView().setCenter(viewX, scene->GetWorldView().getCenter().y);
	}
}

void Stage01::Reset()
{
	bgm.stop();
	scene = SCENE_MGR.GetCurrentScene();

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

	player = new Player();
	potato = new BossPotato();
	onion = new BossOnion();
	carrot = new BossCarrot();

	scene->AddGo(player);

	player->Init();
	potato->Init();
	onion->Init();
	carrot->Init();

	player->Reset();
	potato->Reset();
	onion->Reset();
	carrot->Reset();

	potato->SetPosition({ FRAMEWORK.GetStageViewSize().x * 0.5f * 0.52f, 0.f });
	player->SetPosition({ -playerPosCorrection.x, 0.f });

	potatoHp = potato->GetMaxHp();
	onionHp = onion->GetMaxHp();
	carrotHp = carrot->GetMaxHp();
	totalMaxHp = potatoHp + onionHp + carrotHp;

	bgm.play();
}

void Stage01::Release()
{
	bgm.stop();
	GameObject::Release();
}

void Stage01::Draw(sf::RenderTexture& window)
{

	sf::View& view = scene->GetWorldView();
	sf::View preView = window.getView();

	window.setView(view);
	window.draw(sky);
	window.draw(field11);
	window.draw(field10);
	window.draw(field9);
	window.draw(field8);
	window.draw(field7);
	window.draw(field6);
	window.draw(field5);
	if(phase == 3)
	{
		carrot->Draw(window);
	}
	
	window.draw(field4);
	window.draw(ground);
	if (phase == 1)
	{
		potato->Draw(window);
	}
	else if (phase == 2)
	{
		onion->Draw(window);
	}


	window.draw(frontFlower);
	window.draw(frontFence);
	window.setView(preView);

	GameObject::Draw(window);
}
