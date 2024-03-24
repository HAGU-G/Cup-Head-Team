#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "Stage/Stage01.h"
#include "Effect/ObjectEffect.h"

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
	uiView.setSize(sf::Vector2f(FRAMEWORK.GetWindowSize()));

	for (int i = 2; i <= 51; i++)
	{
		if (i >= 10)
		{
			fightTextMiddle = "00" + std::to_string(i);
		}
		else
		{
			fightTextMiddle = "000" + std::to_string(i);
		}
		RES_MGR_TEXTURE.Load(readyLeft + fightTextMiddle + fightTextRight);
	}

	for (int i = 0; i <= 26; i++)
	{
		if (i >= 10)
		{
			fightTextMiddle = "00" + std::to_string(i);
		}
		else
		{
			fightTextMiddle = "000" + std::to_string(i);
		}
		RES_MGR_TEXTURE.Load(victoryLeft + fightTextMiddle + fightTextRight);
	}

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
	Scene::Update2(dt, pauseWorld);
	MonsterList.erase(std::remove_if(MonsterList.begin(), MonsterList.end(), [](ObjectMonster* monster) { return !monster->IsAlive(); }), MonsterList.end());

	switch (status)
	{
	case SceneGame::Status::None:
		SetStatus(Status::Intro);
		break;
	case SceneGame::Status::Intro:
		timer += dt;
		if (timer >= timeLimit)
		{
			timer = 0.f;
			SetStatus(Status::Fight);
		}
		break;
	case SceneGame::Status::Fight:
		break;
	case SceneGame::Status::Victory:
		timer += dt;
		if (timer >= timeLimit)
		{
			timer = 0.f;
			SetStatus(Status::Exit);
		}
		break;
	case SceneGame::Status::Defeat:
		break;
	default:
		break;
	}
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

void SceneGame::SetStatus(Status status)
{
	this->status = status;
	switch (status)
	{
	case SceneGame::Status::None:
		break;
	case SceneGame::Status::Intro:
		SOUND_MGR.PlaySfx(announcerLeft + "1_" + (char)Utils::RandomRange(97, 102) + announcerRight);
		timer = 0.f;
		timeLimit = 1.f;
		break;
	case SceneGame::Status::Fight:
	{
		ObjectEffect* oe = new ObjectEffect("FightText");
		oe->SetScale({ uiView.getSize().x / 512.f,uiView.getSize().x / 512.f });
		oe->CreateInit(uiView.getCenter(), { 1.f, 0.f }, this, Ui);
		oe->GetAniamtor().Play("animations/fightReady.csv");
		oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
		oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), 20,
			[this]()
			{
				SOUND_MGR.PlaySfx(announcerLeft + "2_" + (char)Utils::RandomRange(97, 102) + announcerRight);
			});
		break;
	}
	case SceneGame::Status::Victory:
	{
		Pause();
		SOUND_MGR.PlaySfx("resource/Menu/sfx_level_announcer_knockout_0004.wav");
		SOUND_MGR.PlaySfx("resource/Menu/sfx_level_knockout_bell.wav");
		ObjectEffect* oe = new ObjectEffect("FightText");
		oe->SetScale({ uiView.getSize().x / 512.f,uiView.getSize().x / 512.f });
		oe->CreateInit(uiView.getCenter(), { 1.f, 0.f }, this, Ui);
		oe->GetAniamtor().Play("animations/fightVictory.csv");
		oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), 23, std::bind(&SceneGame::Play,this));
		oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
		timer = 0.f;
		timeLimit = 10.f;
		break;
	}
	case SceneGame::Status::Defeat:
		break;
	case SceneGame::Status::Exit:
		SCENE_MGR.ChangeScene(SceneIds::SceneTitle);
		Release();
		SetStatus(Status::None);
		break;
	default:
		break;
	}
}