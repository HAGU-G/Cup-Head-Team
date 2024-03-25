#include "pch.h"
#include "SceneTitle.h"
#include "Stage/Stage01.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "UI/ObjectButton.h"

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
	bgm.setVolume(50.f);
	hint.setVolume(25.f);
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

	//옵션
	optionBack = new SpriteGo("Option");
	optionAudio = new ObjectButton("Option");
	optionVisual = new ObjectButton("Option");
	optionEscape = new ObjectButton("Option");

	optionAudio->SetNextButton(optionVisual);
	optionVisual->SetNextButton(optionEscape);
	optionEscape->SetNextButton(optionAudio);

	optionBack->SetTexture("resource/Menu/pause_menu.png");
	optionBack->SetOrigin(Origins::MC);

	optionAudio->SetCharacterSize(textSize);
	optionVisual->SetCharacterSize(textSize);
	optionEscape->SetCharacterSize(textSize);

	optionAudio->SetString(L"오디오");
	optionVisual->SetString(L"비주얼");
	optionEscape->SetString(L"이전");

	optionBack->SetPosition(uiView.getCenter());
	buttonPos = { 0.f, float(-textSize * 2) };
	optionAudio->SetPosition(uiView.getCenter() + buttonPos + sf::Vector2f(textSize * 0.05f, 0.f));
	buttonPos.y += textSize;
	optionVisual->SetPosition(uiView.getCenter() + buttonPos);
	buttonPos.y += textSize;
	optionEscape->SetPosition(uiView.getCenter() + buttonPos);

	optionBack->SetScale(scaleVec);
	sf::Color colorSelect = { 200,50,50,255 };
	optionAudio->SetColorSelect(colorSelect);
	optionVisual->SetColorSelect(colorSelect);
	optionEscape->SetColorSelect(colorSelect);

	optionBack->SetActive(false);
	optionAudio->SetActive(false);
	optionVisual->SetActive(false);
	optionEscape->SetActive(false);

	optionAudio->SetFunction([this]() {
		ChangeStageCard();
		ShowStageCard();
		return optionAudio;
		});
	optionVisual->SetFunction([this]() {
		ShowOption();
		return optionVisual;
		});
	optionEscape->SetFunction([this]() {
		SOUND_MGR.PlaySfx("resource/Menu/Menu_Category_Select.wav");
		ShowOption(false);
		return optionEscape;
		});

	AddGo(optionBack, Ui);
	AddGo(optionAudio, Ui);
	AddGo(optionVisual, Ui);
	AddGo(optionEscape, Ui);

	//Init
	Scene::Init();

	optionAudio->SetOrigin(Origins::TC);
	optionVisual->SetOrigin(Origins::TC);
	optionEscape->SetOrigin(Origins::TC);

	titleReady = true;
}

void SceneTitle::Release()
{
	bgm.stop();
	Scene::Release();
}

void SceneTitle::Enter()
{
	titleReady = false;

	Scene::Enter();
	bgm.stop();
	bgm.openFromFile("resource/Menu/MUS_Intro_DontDealWithDevil_Vocal.wav");
	bgm.play();

	start->Select(false);
	option->UnSelect();
	exit->UnSelect();
	currentButton = start;

	ShowStageCard(false);

	titleReady = true;
}

void SceneTitle::Exit()
{
	bgm.stop();
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
	if (bgm.getStatus() == sf::Sound::Status::Stopped)
	{
		bgm.openFromFile("resource/Menu/MUS_Intro_DontDealWithDevil.wav");
		bgm.play();
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
	else if (isShowOption)
	{
		//옵션 선택
		if (InputMgr::GetKeyDown(sf::Keyboard::Down))
		{
			ButtonSelect();
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Up))
		{
			ButtonSelect(false);
		}

		//버튼 클릭
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			ButtonPress();
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			optionEscape->Press();
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
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			ButtonPress();
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
		bgm.setVolume(10.f);
	}
	else
	{
		hint.stop();
		bgm.setVolume(50.f);
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

	switch (stageNum)
	{
	case 1:
	{
		Stage01* stage01 = new Stage01();
		stage01->Init();
		SCENE_MGR.GetScene(SceneIds::SceneGame)->AddGo(stage01);
		break;
	}
	default:
		return;
	}

	SCENE_MGR.ChangeScene(SceneIds::SceneGame);
}

void SceneTitle::ShowOption(bool value)
{
	if (value)
	{
		bgm.setVolume(10.f);
	}
	else
	{
		currentButton = option;
		//TODO 버튼 전환 오류 고쳐라
		bgm.setVolume(50.f);
	}

	isShowOption = value;

	start->SetActive(!value);
	option->SetActive(!value);
	exit->SetActive(!value);

	optionBack->SetActive(value);
	optionAudio->SetActive(value);
	optionVisual->SetActive(value);
	optionEscape->SetActive(value);

	optionAudio->Select(false);
	optionVisual->UnSelect();
	optionEscape->UnSelect();
	currentButton = optionAudio;
}
