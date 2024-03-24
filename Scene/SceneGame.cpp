#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "Stage/Stage01.h"

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
	Scene::Update(dt);
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
		SOUND_MGR.PlaySfx("resource/Menu/sfx_level_announcer_0001_a.wav");
		timer = 0.f;
		timeLimit = 3.f;
		break;
	case SceneGame::Status::Fight:
		SOUND_MGR.PlaySfx("resource/Menu/sfx_level_announcer_0002_a.wav");
		break;
	case SceneGame::Status::Victory:
		SOUND_MGR.PlaySfx("resource/Menu/sfx_level_announcer_knockout_0004.wav");
		SOUND_MGR.PlaySfx("resource/Menu/sfx_level_knockout_bell.wav");
		timer = 0.f;
		timeLimit = 3.f;
		break;
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