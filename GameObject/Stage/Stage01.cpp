#include "pch.h"
#include "Stage01.h"
#include "Monster/BossPotato.h"
#include "Monster/BossOnion.h"
#include "Monster/BossCarrot.h"

Stage01::Stage01(const std::string& name)
	:GameObject(name)
{
}

void Stage01::Init()
{
}

void Stage01::Update(float dt)
{
	GameObject::Update(dt);
	switch (phase)
	{
	case 0:
		scene->AddGo(potato);
		phase = 1;
		break;
	case 1:
		if (potato->GetHp() <= 0)
		{
			scene->AddGo(onion);
			phase = 2;
		}
		break;
	case 2:
		if (onion->GetHp() <= 0)
		{
			scene->AddGo(carrot);
			phase = 3;
		}
		break;
	case 3:
		if (carrot->GetHp() <= 0)
		{
			
		}
		break;
	default:
		break;
	}
}

void Stage01::Reset()
{
	scene = SCENE_MGR.GetCurrentScene();
	if (potato)
	{
		scene->RemoveGo(potato);
		potato->Release();
		delete potato;
		potato = nullptr;
	}
	if (onion)
	{
		scene->RemoveGo(onion);
		onion->Release();
		delete onion;
		potato = nullptr;
	}
	if (carrot)
	{
		scene->RemoveGo(carrot);
		carrot->Release();
		delete carrot;
		potato = nullptr;
	}

	potato = new BossPotato();
	onion = new BossOnion();
	carrot = new BossCarrot();

	potato->Init();
	onion->Init();
	carrot->Init();

	potato->Reset();
	onion->Reset();
	carrot->Reset();

	potato->SetPosition({ -500,0 });



	totalHp = potato->GetMaxHp() + onion->GetMaxHp() + carrot->GetMaxHp();
}
