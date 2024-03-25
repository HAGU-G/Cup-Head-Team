#include "pch.h"
#include "SceneTitle.h"
#include "Stage/Stage01.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "UI/ObjectButton.h"
#include "Stage/Stage03.h"

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
	buttonPos.y += textSize * 2.f;
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
		ShowOptionAudio();
		return optionAudio;
		});
	optionVisual->SetFunction([this]() {
		ShowOptionVisual();
		return optionVisual;
		});
	optionEscape->SetFunction([this]() {
		SOUND_MGR.PlaySfx("resource/Menu/Menu_Category_Select.wav");
		if (isOptionSelect)
		{
			if (audioText->GetActive()) { ShowOptionAudio(false); }
			if (visualText->GetActive()) { ShowOptionVisual(false); }
		}
		else
		{
			ShowOption(false);
		}

		return optionEscape;
		});

	AddGo(optionBack, Ui);
	AddGo(optionAudio, Ui);
	AddGo(optionVisual, Ui);
	AddGo(optionEscape, Ui);

	//오디오 설정
	audioText = new TextGo("OptionAudio");
	audioMaster = new ObjectButton("OptionAudio");
	audioSfx = new ObjectButton("OptionAudio");
	audioBgm = new ObjectButton("OptionAudio");

	audioMaster->SetNextButton(audioSfx);
	audioSfx->SetNextButton(audioBgm);
	audioBgm->SetNextButton(optionEscape, false);

	audioText->SetCharacterSize(textSize);
	audioMaster->SetCharacterSize(textSize);
	audioSfx->SetCharacterSize(textSize);
	audioBgm->SetCharacterSize(textSize);

	audioText->Set(RES_MGR_FONT.Get("resource/Font/YoonBackjaeM Bold.ttf"), L"마스터 볼륨: \n  SFX 볼륨: \n  음악 볼륨: ", textSize, { 70, 70, 70, 255 });
	audioMaster->SetString("----------l");
	audioSfx->SetString("----------l");
	audioBgm->SetString("----------l");

	audioMaster->SetColorSelect(colorSelect);
	audioSfx->SetColorSelect(colorSelect);
	audioBgm->SetColorSelect(colorSelect);

	audioText->SetActive(false);
	audioMaster->SetActive(false);
	audioSfx->SetActive(false);
	audioBgm->SetActive(false);

	buttonPos = { 0.f, float(-textSize * 3) };
	audioText->SetPosition(uiView.getCenter() + buttonPos);
	audioMaster->SetPosition(uiView.getCenter() + buttonPos);
	buttonPos.y += textSize;
	audioSfx->SetPosition(uiView.getCenter() + buttonPos);
	buttonPos.y += textSize;
	audioBgm->SetPosition(uiView.getCenter() + buttonPos);
	buttonPos.y += textSize;

	AddGo(audioText, Ui);
	AddGo(audioMaster, Ui);
	AddGo(audioSfx, Ui);
	AddGo(audioBgm, Ui);

	//그래픽 설정
	visualText = new TextGo("OptionVisual");
	visualBleeding = new ObjectButton("OptionVisual");

	visualBleeding->SetNextButton(optionEscape, false);

	visualText->SetCharacterSize(textSize);
	visualBleeding->SetCharacterSize(textSize);

	visualText->Set(RES_MGR_FONT.Get("resource/Font/YoonBackjaeM Bold.ttf"), L"색 번짐: ", textSize, { 70, 70, 70, 255 });
	visualBleeding->SetString("-----l-----");

	visualBleeding->SetColorSelect(colorSelect);

	visualText->SetActive(false);
	visualBleeding->SetActive(false);

	buttonPos = { 0.f, float(-textSize * 3) };
	visualText->SetPosition(uiView.getCenter() + buttonPos);
	visualBleeding->SetPosition(uiView.getCenter() + buttonPos);
	buttonPos.y += textSize;

	AddGo(visualText, Ui);
	AddGo(visualBleeding, Ui);

	//Init
	Scene::Init();

	optionAudio->SetOrigin(Origins::TC);
	optionVisual->SetOrigin(Origins::TC);
	optionEscape->SetOrigin(Origins::TC);

	audioMaster->SetFont("resource/Font/CupheadVogue-ExtraBold.ttf");
	audioSfx->SetFont("resource/Font/CupheadVogue-ExtraBold.ttf");
	audioBgm->SetFont("resource/Font/CupheadVogue-ExtraBold.ttf");
	audioText->SetOrigin(Origins::TR);
	audioMaster->SetOrigin(Origins::TL);
	audioSfx->SetOrigin(Origins::TL);
	audioBgm->SetOrigin(Origins::TL);

	visualBleeding->SetFont("resource/Font/CupheadVogue-ExtraBold.ttf");
	visualText->SetOrigin(Origins::TR);
	visualBleeding->SetOrigin(Origins::TL);

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

	ShowStageCard(false);

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
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			ButtonPress();
		}

		if (isOptionSelect && InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			optionEscape->Press();
		}

		if (isShowOption)
		{
			if (InputMgr::GetKeyDown(sf::Keyboard::Left))
			{
				std::string indicator = currentButton->GetText().getString();
				float value = 10.f;
				if ((value *= indicator.find('l')) > 0.f)
				{
					indicator.erase(indicator.begin());
					indicator.push_back('-');
					currentButton->SetString(indicator);
					if (currentButton == audioMaster) { sf::Listener::setGlobalVolume(value - 10.f); }
					else if (currentButton == audioSfx) { SOUND_MGR.SetSfxVolume(value - 10.f); }
					else if (currentButton == audioBgm) { SOUND_MGR.SetBgmVolume(value - 10.f); }
					else if (currentButton == visualBleeding) { FRAMEWORK.SetBleedingValue((value - 10.f) / 100.f); }
					SOUND_MGR.PlaySfx("resource/Menu/Menu_Category_Select.wav");
				}
			}
			else if (InputMgr::GetKeyDown(sf::Keyboard::Right))
			{
				std::string indicator = currentButton->GetText().getString();
				float value = 10.f;
				if ((value *= indicator.find('l')) < 100.f)
				{
					indicator.pop_back();
					indicator.insert(indicator.begin(), '-');
					currentButton->SetString(indicator);
					if (currentButton == audioMaster) { sf::Listener::setGlobalVolume(value + 10.f); }
					else if (currentButton == audioSfx) { SOUND_MGR.SetSfxVolume(value + 10.f); }
					else if (currentButton == audioBgm) { SOUND_MGR.SetBgmVolume(value + 10.f); }
					else if (currentButton == visualBleeding) { FRAMEWORK.SetBleedingValue((value + 10.f) / 100.f); }
					SOUND_MGR.PlaySfx("resource/Menu/Menu_Category_Select.wav");
				}
			}
			if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
			{
				optionEscape->Press();
			}
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
}

void SceneTitle::ShowOption(bool value)
{
	if (value)
	{
		optionAudio->Select(false);
		optionVisual->UnSelect();
		optionEscape->UnSelect();
		currentButton = optionAudio;
	}
	else
	{
		currentButton = option;
	}

	isShowOption = value;

	start->SetActive(!value);
	option->SetActive(!value);
	exit->SetActive(!value);

	optionBack->SetActive(value);
	optionAudio->SetActive(value);
	optionVisual->SetActive(value);
	optionEscape->SetActive(value);

}

void SceneTitle::ShowOptionAudio(bool value)
{
	if (value)
	{
		audioMaster->Select(false);
		audioSfx->UnSelect();
		audioBgm->UnSelect();
		currentButton = audioMaster;

		audioBgm->SetNextButton(optionEscape);
		optionEscape->SetNextButton(audioMaster);
	}
	else
	{
		currentButton = optionAudio;

		optionEscape->UnSelect();
		optionVisual->SetNextButton(optionEscape);
		optionEscape->SetNextButton(optionAudio);
	}

	isOptionSelect = value;

	optionAudio->SetActive(!value);
	optionVisual->SetActive(!value);

	audioText->SetActive(value);
	audioMaster->SetActive(value);
	audioSfx->SetActive(value);
	audioBgm->SetActive(value);
}

void SceneTitle::ShowOptionVisual(bool value)
{
	if (value)
	{
		visualBleeding->Select(false);
		currentButton = visualBleeding;

		visualBleeding->SetNextButton(optionEscape);
		optionEscape->SetNextButton(visualBleeding);
	}
	else
	{
		currentButton = optionVisual;

		optionEscape->UnSelect();
		optionVisual->SetNextButton(optionEscape);
		optionEscape->SetNextButton(optionAudio);
	}

	isOptionSelect = value;

	optionAudio->SetActive(!value);
	optionVisual->SetActive(!value);

	visualText->SetActive(value);
	visualBleeding->SetActive(value);
}
