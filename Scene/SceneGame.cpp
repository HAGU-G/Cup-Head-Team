#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "Stage/Stage01.h"
#include "Effect/ObjectEffect.h"
#include "Bullet/ObjectBullet.h"
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
	Pause();
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
	monsterList.clear();
	toeholdList.clear();
	enemyBulletList.clear();
	option = nullptr;
	playerHp = nullptr;
}

void SceneGame::Enter()
{
	Scene::Enter();

	option = dynamic_cast<ObjectOption*>(AddGo(new ObjectOption("Option"), Ui));
	option->SetScene(this);
	option->Init();
	option->Reset();
	option->SetActive(false);

	playerHp = new SpriteGo("PlayerHp");
	playerHp->GetAnimator().SetTarget(&playerHp->GetSprite());
	playerHp->SetTexture("resource/FightText/hud_hp_3.png");
	playerHp->SetOrigin(Origins::BL);
	playerHp->SetPosition(uiView.getCenter() + sf::Vector2f(-uiView.getSize().x, uiView.getSize().y) * 0.48f);
	playerHp->Init();
	playerHp->Reset();
	AddGo(playerHp, Ui);
}

void SceneGame::Exit()
{
	Pause();
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	if (isParryed)
	{
		isParryed = false;
		parryEffectTimer = 0.0f;
	}


	if (parryEffectTimer >= parryEffectDuration)
	{
		Play();
		parryEffectTimer = -1.f;
	}
	else if (parryEffectTimer >= 0.f)
	{
		parryEffectTimer += dt;
	}

	Scene::Update2(dt, pauseWorld);

	switch (status)
	{
	case SceneGame::Status::None:
		SetStatus(Status::Intro);
		break;
	case SceneGame::Status::Intro:
		Play();
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

void SceneGame::LateUpdate(float dt)
{
	//Scene::LateUpdate
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->LateUpdate(dt);
		}
	}

	for (auto obj : uiGameObjects)
	{
		if (obj->GetActive())
		{
			obj->LateUpdate(dt);
		}
	}

	//충돌검사용 리스트 갱신
	auto itM = monsterList.begin();
	while (itM != monsterList.end())
	{
		if (!(*itM)->IsAlive())
		{
			itM = monsterList.erase(itM);
		}
		else
		{
			itM++;
		}
	}
	auto itT = toeholdList.begin();
	while (itT != toeholdList.end())
	{
		if (!(*itT)->GetActive())
		{
			itT = toeholdList.erase(itT);
		}
		else
		{
			itT++;
		}
	}
	auto itE = enemyBulletList.begin();
	while (itE != enemyBulletList.end())
	{
		if (!(*itE)->IsAlive())
		{
			itE = enemyBulletList.erase(itE);
		}
		else
		{
			itE++;
		}
	}

	//Scene::LateUpdate
	for (auto obj : removeGameObjects)
	{
		gameObjects.remove(obj);
		uiGameObjects.remove(obj);

		delete obj;
	}
	removeGameObjects.clear();

	for (auto obj : resortingGameObjects)
	{
		auto it = std::find(gameObjects.begin(), gameObjects.end(), obj);
		if (it != gameObjects.end())
		{
			gameObjects.remove(obj);
			AddGo(obj, Layers::World);
			continue;
		}

		it = std::find(uiGameObjects.begin(), uiGameObjects.end(), obj);
		if (it != uiGameObjects.end())
		{
			uiGameObjects.remove(obj);
			AddGo(obj, Layers::Ui);
			continue;
		}
	}



	//toeholdList.erase(std::remove_if(toeholdList.begin(), toeholdList.end(), [](SpriteGo* toehold) { return !toehold->GetActive(); }), toeholdList.end());

}

void SceneGame::Draw(sf::RenderTexture& window)
{
	Scene::Draw(window);
}

void SceneGame::AddMonster(ObjectMonster* monster)
{
	monsterList.push_back(monster);
}

const std::list<ObjectMonster*>& SceneGame::GetAllMonsters() const
{
	return monsterList;
}

void SceneGame::Addtoehold(SpriteGo* toehold)
{
	toeholdList.push_back(toehold);
}

const std::vector<SpriteGo*>& SceneGame::GetAlltoehold() const
{
	return toeholdList;
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
		oe->GetAnimator().Play("animations/fightReady.csv");
		oe->GetAnimator().AddEvent(oe->GetAnimator().GetCurrentCilpId(), 20,
			[this]()
			{
				SOUND_MGR.PlaySfx(announcerLeft + "2_" + (char)Utils::RandomRange(97, 102) + announcerRight);
			});
		oe->GetAnimator().AddEvent(oe->GetAnimator().GetCurrentCilpId(), oe->GetAnimator().GetCurrentClip()->GetTotalFrame(),
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
		oe->GetAnimator().Play("animations/fightVictory.csv");
		oe->GetAnimator().AddEvent(oe->GetAnimator().GetCurrentCilpId(), 23, std::bind(&SceneGame::Play, this));
		oe->GetAnimator().AddEvent(oe->GetAnimator().GetCurrentCilpId(), oe->GetAnimator().GetCurrentClip()->GetTotalFrame(), std::bind(&ObjectEffect::OnDie, oe));
		timer = 0.f;
		timeLimit = 6.f;
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
		timeLimit = 3.f;
		break;
	}
	case SceneGame::Status::Exit:
		SCENE_MGR.ChangeScene(SceneIds::SceneTitle);
		RES_MGR_SOUND_BUFFER.UnloadAll();
		RES_MGR_TEXTURE.UnloadAll();
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

void SceneGame::SetPlayerHp(int i)
{
	if (i <= 0)
	{
		playerHp->GetAnimator().Stop();
		playerHp->SetTexture("resource/FightText/hud_hp_dead.png");
		if (status < SceneGame::Status::Defeat)
		{
			SetStatus(SceneGame::Status::Defeat);
		}
	}
	else if (i == 1)
	{
		playerHp->GetAnimator().Play("animations/hud_hp_1.csv");
	}
	else if (i >= 9)
	{
		playerHp->GetAnimator().Stop();
		playerHp->SetTexture("resource/FightText/hud_hp_9.png");
	}
	else
	{
		playerHp->GetAnimator().Stop();
		playerHp->SetTexture("resource/FightText/hud_hp_" + std::to_string(i) + ".png");
	}
}

void SceneGame::AddEnemyBullet(ObjectBullet* enemyBullet)
{
	enemyBulletList.push_back(enemyBullet);
}

const std::deque<ObjectBullet*>& SceneGame::GetAllEnemyBullet() const
{
	return enemyBulletList;
}
