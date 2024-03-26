#include "pch.h"
#include "SceneTitle.h"
#include "Stage/Stage01.h"
#include "Stage/Stage02.h"
#include "Stage/Stage03.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "UI/ObjectButton.h"
#include "UI/ObjectOption.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	titleReady = false;

	sf::Vector2f windowSize = sf::Vector2f(FRAMEWORK.GetWindowSize());
	worldView.setSize(windowSize);
	uiView.setSize(windowSize);
	textSize = 50 * windowSize.y / 1080;

	//배경음악
	SOUND_MGR.SetBgmVolume(50.f);
	hint.setVolume(SOUND_MGR.GetBgmVolume() * 0.5f);
	hint.setLoop(true);

	//배경
	bg = new SpriteGo("Background");
	bg->SetTexture("resource/Menu/cuphead_secondary_title_screen.png");
	float scale = std::max(worldView.getSize().x / bg->GetSize().x, worldView.getSize().y / bg->GetSize().y);
	sf::Vector2f scaleVec = { scale, scale }; //스테이지 카드 SetScale에서도 사용.
	bg->SetScale(scaleVec);
	bg->SetOrigin(Origins::MC);
	bg->SetPosition(worldView.getCenter());
	AddGo(bg);

	//버튼
	start = new ObjectButton("Start");
	option = new ObjectButton("Option");
	exit = new ObjectButton("Exit");

	start->SetNextButton(option);
	option->SetNextButton(exit);
	exit->SetNextButton(start);

	start->SetOrigin(Origins::BC);
	option->SetOrigin(Origins::BC);
	exit->SetOrigin(Origins::BC);

	start->SetString(L"시작");
	option->SetString(L"옵션");
	exit->SetString(L"종료");

	start->SetCharacterSize(textSize);
	option->SetCharacterSize(textSize);
	exit->SetCharacterSize(textSize);

	start->SetFunction([this]() {
		ChangeStageCard();
		ShowStageCard();
		return start;
		});
	option->SetFunction([this]() {
		ShowOption();
		return option;
		});
	exit->SetFunction([this]() {
		FRAMEWORK.GetWindowReal().close();
		return exit;
		});

	sf::Vector2f buttonPos = { float(-textSize), float(-textSize * 3) };
	start->SetPosition(uiView.getCenter() + buttonPos);
	buttonPos.y += textSize;
	option->SetPosition(uiView.getCenter() + buttonPos);
	buttonPos.y += textSize;
	exit->SetPosition(uiView.getCenter() + buttonPos);

	AddGo(start, Ui);
	AddGo(option, Ui);
	AddGo(exit, Ui);

	//스테이지 카드
	stageCardBack = new SpriteGo("StageCard");
	stageCardGlow = new SpriteGo("StageCard");
	stageCardX = new TextGo("StageCard");
	stageCardName = new SpriteGo("StageCard");
	stageCardTitle = new SpriteGo("StageCard");
	stageCardNotReady = new SpriteGo("StageCard");

	stageCardBack->SetTexture("resource/Menu/title_card_background.png");
	stageCardBack->SetOrigin(Origins::MC);
	stageCardNotReady->SetTexture("resource/Menu/COMING SOON.png");
	stageCardNotReady->SetOrigin(Origins::MC);
	stageCardGlow->SetAlpha(40);

	stageCardX->Set(RES_MGR_FONT.Get("resource/Font/YoonBackjaeM Bold.ttf"), "X", textSize, sf::Color::White);
	stageCardX->SetOrigin(Origins::MC);

	stageCardBack->SetPosition(uiView.getCenter());
	stageCardGlow->SetPosition(uiView.getCenter());
	stageCardNotReady->SetPosition(uiView.getCenter());

	stageCardBack->SetScale(scaleVec * 1.1f);
	stageCardGlow->SetScale(scaleVec * 1.1f);
	stageCardName->SetScale(scaleVec * 0.375f);
	stageCardTitle->SetScale(scaleVec * 0.375f);
	stageCardNotReady->SetScale(scaleVec * 3.f);

	stageCardBack->SetActive(false);
	stageCardGlow->SetActive(false);
	stageCardX->SetActive(false);
	stageCardName->SetActive(false);
	stageCardTitle->SetActive(false);
	stageCardNotReady->SetActive(false);

	AddGo(stageCardBack, Ui);
	AddGo(stageCardGlow, Ui);
	AddGo(stageCardX, Ui);
	AddGo(stageCardName, Ui);
	AddGo(stageCardTitle, Ui);
	AddGo(stageCardNotReady, Ui);

	//Init
	Scene::Init();

	//옵션 버튼
	optionCard = dynamic_cast<ObjectOption*>(AddGo(new ObjectOption("OptionCard")));
	optionCard->SetScene(this);
	optionCard->Init();
	optionCard->Reset();
	optionCard->SetActive(false);

	titleReady = true;
}

void SceneTitle::Release()
{
	SOUND_MGR.StopBgm();
	Scene::Release();
}

void SceneTitle::Enter()
{
	titleReady = false;

	Scene::Enter();
	SOUND_MGR.StopBgm();
	SOUND_MGR.PlayBgm("resource/Menu/MUS_Intro_DontDealWithDevil_Vocal.wav", true, false);

	start->Select(false);
	option->UnSelect();
	exit->UnSelect();
	currentButton = start;

	titleReady = true;
}

void SceneTitle::Exit()
{
	SOUND_MGR.StopBgm();
	hint.stop();
	Scene::Exit();
}

void SceneTitle::Draw(sf::RenderTexture& window)
{
	Scene::Draw(window);
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	//배경음악2 반복재생
	if (!SOUND_MGR.IsBgmPlaying())
	{
		SOUND_MGR.PlayBgm("resource/Menu/MUS_Intro_DontDealWithDevil.wav", false, true);
	}

	if (isShowOption)
	{
		return;
	}

	if (isShowStageCard)
	{
		//카드 선택
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			SOUND_MGR.PlaySfx("resource/Menu/sfx_WorldMap_LevelSelect_DiffucultySettings_Hover.wav");
			stageNum++;
			if (stageNum > 3)
			{
				stageNum = 1;
			}

			ChangeStageCard();
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			SOUND_MGR.PlaySfx("resource/Menu/sfx_WorldMap_LevelSelect_DiffucultySettings_Hover.wav");
			stageNum--;
			if (stageNum < 1)
			{
				stageNum = 3;
			}

			ChangeStageCard();
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			ShowStageCard(false);
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			StartGame();
		}
	}
	else
	{
		//버튼 선택
		if (InputMgr::GetKeyDown(sf::Keyboard::Down))
		{
			ButtonSelect();
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Up))
		{
			ButtonSelect(false);
		}

		//버튼 클릭
		if (InputMgr::GetKeyDown(sf::Keyboard::Z) && !optionCard->GetActive())
		{
			ButtonPress();
		}
		if (!isShowOption && optionCard->GetActive())
		{
			optionCard->SetActive(false);
		}
	}
}

void SceneTitle::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneTitle::ButtonSelect(bool direction)
{
	currentButton = currentButton->ButtonMove(direction);
}

void SceneTitle::ButtonPress()
{
	currentButton->Press();
}

void SceneTitle::ShowStageCard(bool value)
{
	if (value)
	{
		SOUND_MGR.PlaySfx("resource/Menu/sfx_WorldMap_LevelSelect_DiffucultySettings_Appear.wav");
		bgmVolume = SOUND_MGR.GetBgmVolume();
		SOUND_MGR.SetBgmVolume(SOUND_MGR.GetBgmVolume() / 5.f);
	}
	else
	{
		hint.stop();
		SOUND_MGR.SetBgmVolume(bgmVolume);
		stageCardNotReady->SetActive(value);
	}

	isShowStageCard = value;

	start->SetActive(!value);
	option->SetActive(!value);
	exit->SetActive(!value);

	stageCardBack->SetActive(value);
	stageCardGlow->SetActive(value);
	stageCardX->SetActive(value);
	stageCardName->SetActive(value);
	stageCardTitle->SetActive(value);

}

void SceneTitle::ChangeStageCard()
{
	hint.stop();
	switch (stageNum)
	{
	case 1:
		hint.setBuffer(RES_MGR_SOUND_BUFFER.Get("resource/Menu/sfx_worldmap_hint_veggies.wav"));

		stageCardGlow->SetTexture("resource/Menu/title_card_veggie_kr_glow.png");
		stageCardName->SetTexture("resource/Menu/boss_name_veggie_kr.png");
		stageCardTitle->SetTexture("resource/Menu/title_card_veggie_kr.png");

		stageCardGlow->SetOrigin(Origins::MC);
		stageCardName->SetOrigin(Origins::TC);
		stageCardTitle->SetOrigin(Origins::BC);

		stageCardName->SetPosition(stageCardGlow->GetPosition() + sf::Vector2f(0.f, -stageCardGlow->GetGlobalBounds().height * 0.475f));
		stageCardTitle->SetPosition(stageCardGlow->GetPosition() + sf::Vector2f(0.f, stageCardGlow->GetGlobalBounds().height * 0.675f));
		stageCardX->SetPosition(stageCardGlow->GetPosition() + sf::Vector2f(0.f, -stageCardGlow->GetGlobalBounds().height * 0.20f));
		stageCardNotReady->SetActive(false);
		break;
	case 2:
		hint.setBuffer(RES_MGR_SOUND_BUFFER.Get("resource/Menu/sfx_worldmap_frogs.wav"));

		stageCardGlow->SetTexture("resource/Menu/title_card_frogs_kr_glow.png");
		stageCardName->SetTexture("resource/Menu/boss_name_frogs_kr.png");
		stageCardTitle->SetTexture("resource/Menu/title_card_frogs_kr.png");

		stageCardGlow->SetOrigin(Origins::MC);
		stageCardName->SetOrigin(Origins::TC);
		stageCardTitle->SetOrigin(Origins::BC);

		stageCardName->SetPosition(stageCardGlow->GetPosition() + sf::Vector2f(0.f, -stageCardGlow->GetGlobalBounds().height * 0.45f));
		stageCardTitle->SetPosition(stageCardGlow->GetPosition() + sf::Vector2f(0.f, stageCardGlow->GetGlobalBounds().height * 0.475f));
		stageCardX->SetPosition(stageCardGlow->GetPosition() + sf::Vector2f(0.f, -stageCardGlow->GetGlobalBounds().height * 0.275f));
		stageCardNotReady->SetActive(true);
		break;
	case 3:
		hint.setBuffer(RES_MGR_SOUND_BUFFER.Get("resource/Menu/sfx_worldmap_hint_flower.wav"));

		stageCardGlow->SetTexture("resource/Menu/title_card_flower_kr_glow.png");
		stageCardName->SetTexture("resource/Menu/boss_name_flower_kr.png");
		stageCardTitle->SetTexture("resource/Menu/title_card_flower_kr.png");

		stageCardGlow->SetOrigin(Origins::MC);
		stageCardName->SetOrigin(Origins::TC);
		stageCardTitle->SetOrigin(Origins::BC);

		stageCardName->SetPosition(stageCardGlow->GetPosition() + sf::Vector2f(0.f, -stageCardGlow->GetGlobalBounds().height * 0.45f));
		stageCardTitle->SetPosition(stageCardGlow->GetPosition() + sf::Vector2f(0.f, stageCardGlow->GetGlobalBounds().height * 0.60f));
		stageCardX->SetPosition(stageCardGlow->GetPosition() + sf::Vector2f(0.f, -stageCardGlow->GetGlobalBounds().height * 0.20f));
		stageCardNotReady->SetActive(true);
		break;
	default:
		break;
	}

	if (titleReady)
	{
		hint.play();
	}

}

void SceneTitle::StartGame()
{
	SOUND_MGR.PlaySfx("resource/Menu/sfx_WorldMap_LevelSelect_StartLevel.wav");
	SOUND_MGR.SetBgmVolume(bgmVolume);
	switch (stageNum)
	{
	case 1:
	{
		Stage01* stage01 = new Stage01();
		stage01->Init();
		SCENE_MGR.GetScene(SceneIds::SceneGame)->AddGo(stage01);
		break;
	}
	case 2:
	{
		Stage02* stage02 = new Stage02();
		stage02->Init();
		SCENE_MGR.GetScene(SceneIds::SceneGame)->AddGo(stage02);
		break;
	}
	case 3:
	{
		Stage03* stage03 = new Stage03();
		stage03->Init();
		SCENE_MGR.GetScene(SceneIds::SceneGame)->AddGo(stage03);
		break;
	}
	default:
		return;
	}

	SCENE_MGR.ChangeScene(SceneIds::SceneGame);
	ShowStageCard(false);
}

void SceneTitle::ShowOption(bool value)
{
	if (value)
	{
		optionCard->SetActive(true);
		optionCard->ShowOption(true);
	}
	isShowOption = value;

	start->SetActive(!value);
	option->SetActive(!value);
	exit->SetActive(!value);

}