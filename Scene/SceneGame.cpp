#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "Stage/Stage01.h"
#include "Effect/ObjectEffect.h"
#include "UI/ObjectOption.h"
#include "SceneTitle.h"

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
	MonsterList.clear();
}

void SceneGame::Enter()
{
	Scene::Enter();
	option = dynamic_cast<ObjectOption*>(AddGo(new ObjectOption("Option"), Ui));
	option->SetScene(this);
	option->Init();
	option->Reset();
	option->SetActive(false);
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
			SetStatus(Status::FightIntro);
		}
		break;
	case SceneGame::Status::FightIntro:
		break;
	case SceneGame::Status::Fight:
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			Pause();
			option->SetActive(true);
			option->ShowOption();
			SetStatus(Status::Option);
		}
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
		timer += dt;
		if (timer >= timeLimit)
		{
			timer = 0.f;
			SetStatus(Status::Exit);
		}
		break;
	case SceneGame::Status::Option:
		if (!option->GetActive())
		{
			SetStatus(Status::Fight);
		}
		break;
	case SceneGame::Status::GoTitle:
		SetStatus(Status::Exit);
		break;
	case SceneGame::Status::Reset:
		SetStatus(Status::Reset);
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
	if (status != Status::Reset)
	{
		this->status = status;
	}
	switch (status)
	{
	case SceneGame::Status::None:
		break;
	case SceneGame::Status::Intro:
		SOUND_MGR.PlaySfx(announcerLeft + "1_" + (char)Utils::RandomRange(97, 102) + announcerRight);
		timer = 0.f;
		timeLimit = 1.5f;
		break;
	case SceneGame::Status::FightIntro:
	{
		ObjectEffect* oe = new ObjectEffect("FightText");
		oe->SetScale({ uiView.getSize().x / 512.f,uiView.getSize().x / 512.f });
		oe->CreateInit(uiView.getCenter(), { 1.f, 0.f }, this, Ui);
		oe->GetAniamtor().Play("animations/fightReady.csv");
		oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), 20,
			[this]()
			{
				SOUND_MGR.PlaySfx(announcerLeft + "2_" + (char)Utils::RandomRange(97, 102) + announcerRight);
			});
		oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(),
			[oe, this]()
			{
				oe->OnDie();
				this->SetStatus(Status::Fight);
			});
		break;
	}
	case SceneGame::Status::Fight:
		break;
	case SceneGame::Status::Victory:
	{
		Pause();
		SOUND_MGR.PlaySfx("resource/Menu/sfx_level_announcer_knockout_0004.wav");
		SOUND_MGR.PlaySfx("resource/Menu/sfx_level_knockout_bell.wav");
		ObjectEffect* oe = new ObjectEffect("FightText");
		oe->SetScale({ uiView.getSize().x / 512.f,uiView.getSize().x / 512.f });
		oe->CreateInit(uiView.getCenter(), { 1.f, 0.f }, this, Ui);
		oe->GetAniamtor().Play("animations/fightVictory.csv");
		oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), 23, std::bind(&SceneGame::Play, this));
		oe->GetAniamtor().AddEvent(oe->GetAniamtor().GetCurrentCilpId(), oe->GetAniamtor().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
		timer = 0.f;
		timeLimit = 10.f;
		break;
	}
	case SceneGame::Status::Defeat:
	{
		SOUND_MGR.PlaySfx("resource/FightText/sfx_player_death_0" + std::to_string(Utils::RandomRange(1, 3)) + ".wav");
		ObjectEffect* oe = new ObjectEffect("FightText");
		oe->CreateInit(uiView.getCenter(), { 1.f, 0.f }, this, Ui);
		oe->SetTexture("resource/FightText/you_died_text_0001.png");
		oe->SetOrigin(Origins::MC);
		oe->SetDieByTime(3.f, true);
		timer = 0.f;
		timeLimit = 5.f;
		break;
	}
	case SceneGame::Status::Exit:
		SCENE_MGR.ChangeScene(SceneIds::SceneTitle);
		Release();
		SetStatus(Status::None);
		break;
	case SceneGame::Status::Reset:
		if (this->status == Status::Reset)
		{
			Release();
			SetStatus(Status::None);
			dynamic_cast<SceneTitle*>(SCENE_MGR.GetScene(SceneIds::SceneTitle))->StartGame();
		}
		else
		{
			this->status = status;
		}
		break;
	}

}