#include "pch.h"
#include "ObjectOption.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "UI/ObjectButton.h"
#include "SceneGame.h"
#include "SceneTitle.h"

ObjectOption::ObjectOption(const std::string& name)
	:GameObject(name)
{
}

void ObjectOption::Init()
{
	textSize = 50 * FRAMEWORK.GetWindowSize().y / 1080;
	sf::Vector2f buttonPos = { float(-textSize), float(-textSize * 3) };
	SpriteGo* bg = new SpriteGo("Background");
	bg->SetTexture("resource/Menu/cuphead_secondary_title_screen.png");
	float scale = std::max(scene->GetWorldView().getSize().x / bg->GetSize().x, scene->GetWorldView().getSize().y / bg->GetSize().y);
	sf::Vector2f scaleVec = { scale, scale };

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

	optionBack->SetPosition(scene->GetUiView().getCenter());
	buttonPos = { 0.f, float(-textSize * 2) };
	optionAudio->SetPosition(scene->GetUiView().getCenter() + buttonPos + sf::Vector2f(textSize * 0.05f, 0.f));
	buttonPos.y += textSize;
	optionVisual->SetPosition(scene->GetUiView().getCenter() + buttonPos);
	buttonPos.y += textSize * 2.f;
	optionEscape->SetPosition(scene->GetUiView().getCenter() + buttonPos);

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

	scene->AddGo(optionBack, Scene::Ui);
	scene->AddGo(optionAudio, Scene::Ui);
	scene->AddGo(optionVisual, Scene::Ui);
	scene->AddGo(optionEscape, Scene::Ui);

	if (scene->GetId() == SceneIds::SceneGame)
	{
		reStart = new ObjectButton("Option");
		goTitle = new ObjectButton("Option");

		reStart->SetNextButton(optionAudio);
		optionAudio->SetNextButton(optionVisual);
		optionVisual->SetNextButton(goTitle);
		goTitle->SetNextButton(optionEscape);
		optionEscape->SetNextButton(reStart);

		reStart->SetCharacterSize(textSize);
		goTitle->SetCharacterSize(textSize);

		reStart->SetString(L"재시작");
		goTitle->SetString(L"타이틀로 돌아가기");

		reStart->SetColorSelect(colorSelect);
		goTitle->SetColorSelect(colorSelect);

		reStart->SetFunction([this]() {
			ShowOption(false);
			SceneGame* sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));
			sceneGame->SetStatus(SceneGame::Status::Reset);
			sceneGame->Play();
			return reStart;
			});
		goTitle->SetFunction([this]() {
			SceneGame* sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));
			sceneGame->SetStatus(SceneGame::Status::GoTitle);
			sceneGame->Play();
			return goTitle;
			});

		buttonPos.y -= textSize;
		goTitle->SetPosition(scene->GetUiView().getCenter() + buttonPos);
		buttonPos.y -= textSize * 3.f;
		reStart->SetPosition(scene->GetUiView().getCenter() + buttonPos);

		reStart->SetActive(false);
		goTitle->SetActive(false);

		scene->AddGo(reStart, Scene::Ui);
		scene->AddGo(goTitle, Scene::Ui);
	}


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
	audioText->SetPosition(scene->GetUiView().getCenter() + buttonPos);
	audioMaster->SetPosition(scene->GetUiView().getCenter() + buttonPos);
	buttonPos.y += textSize;
	audioSfx->SetPosition(scene->GetUiView().getCenter() + buttonPos);
	buttonPos.y += textSize;
	audioBgm->SetPosition(scene->GetUiView().getCenter() + buttonPos);
	buttonPos.y += textSize;

	scene->AddGo(audioText, Scene::Ui);
	scene->AddGo(audioMaster, Scene::Ui);
	scene->AddGo(audioSfx, Scene::Ui);
	scene->AddGo(audioBgm, Scene::Ui);

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
	visualText->SetPosition(scene->GetUiView().getCenter() + buttonPos);
	visualBleeding->SetPosition(scene->GetUiView().getCenter() + buttonPos);
	buttonPos.y += textSize;

	scene->AddGo(visualText, Scene::Ui);
	scene->AddGo(visualBleeding, Scene::Ui);

	//Init
	GameObject::Init();
	optionBack->Init();
	optionAudio->Init();
	optionVisual->Init();
	optionEscape->Init();
	audioText->Init();
	audioMaster->Init();
	audioBgm->Init();
	audioSfx->Init();
	visualText->Init();
	visualBleeding->Init();

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

	currentButton = optionAudio;

	if (reStart)
	{
		reStart->Init();
		goTitle->Init();
		reStart->SetOrigin(Origins::TC);
		goTitle->SetOrigin(Origins::TC);
		reStart->Select(false);
	}
	else
	{
		optionAudio->Select(false);
	}

	delete bg;
}

void ObjectOption::Update(float dt)
{
	GameObject::Update(dt);

	if (!isShowOption) { return; }

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
	if (InputMgr::GetKeyDown(sf::Keyboard::Z) || InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		ButtonPress();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Left) && (
		currentButton == audioMaster
		|| currentButton == audioSfx
		|| currentButton == audioBgm
		|| currentButton == visualBleeding))
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
	else if (InputMgr::GetKeyDown(sf::Keyboard::Right) && (
		currentButton == audioMaster
		|| currentButton == audioSfx
		|| currentButton == audioBgm
		|| currentButton == visualBleeding))
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

void ObjectOption::Reset()
{
	GameObject::Reset();
	optionBack->Reset();
	optionAudio->Reset();
	optionVisual->Reset();
	optionEscape->Reset();
	audioText->Reset();
	audioMaster->Reset();
	audioBgm->Reset();
	audioSfx->Reset();
	visualText->Reset();
	visualBleeding->Reset();
	if (reStart)
	{
		reStart->Reset();
		goTitle->Reset();
	}
}

void ObjectOption::Release()
{
	GameObject::Release();

	scene->RemoveGo(optionBack);
	scene->RemoveGo(optionAudio);
	scene->RemoveGo(optionVisual);
	scene->RemoveGo(optionEscape);

	scene->RemoveGo(audioText);
	scene->RemoveGo(audioMaster);
	scene->RemoveGo(audioBgm);
	scene->RemoveGo(audioSfx);

	scene->RemoveGo(visualText);
	scene->RemoveGo(visualBleeding);

	if (reStart)
	{
		scene->RemoveGo(reStart);
		scene->RemoveGo(goTitle);
	}
}

void ObjectOption::ButtonSelect(bool direction)
{
	currentButton = currentButton->ButtonMove(direction);
}

void ObjectOption::ButtonPress()
{
	currentButton->Press();
}

void ObjectOption::ShowOption(bool value)
{
	if (value)
	{
		if (reStart)
		{
			reStart->Select(false);
			optionAudio->UnSelect();
			optionVisual->UnSelect();
			goTitle->UnSelect();
			optionEscape->UnSelect();
			currentButton = reStart;
		}
		else
		{
			optionAudio->Select(false);
			optionVisual->UnSelect();
			optionEscape->UnSelect();
			currentButton = optionAudio;
		}
	}
	else
	{
		currentButton = optionAudio;
		if (scene->GetId() == SceneIds::SceneGame)
		{
			SetActive(false);
			dynamic_cast<SceneGame*>(scene)->Play();
		}
		else if (scene->GetId() == SceneIds::SceneTitle)
		{
			dynamic_cast<SceneTitle*> (scene)->ShowOption(false);
		}
	}

	isShowOption = value;

	optionBack->SetActive(value);
	optionAudio->SetActive(value);
	optionVisual->SetActive(value);
	optionEscape->SetActive(value);
	if (reStart)
	{
		reStart->SetActive(value);
		goTitle->SetActive(value);
	}
}

void ObjectOption::ShowOptionAudio(bool value)
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
		if (reStart)
		{
			goTitle->SetNextButton(optionEscape);
			optionEscape->SetNextButton(reStart);
		}
		else
		{
			optionVisual->SetNextButton(optionEscape);
			optionEscape->SetNextButton(optionAudio);
		}
	}

	isOptionSelect = value;

	optionAudio->SetActive(!value);
	optionVisual->SetActive(!value);
	if (reStart)
	{
		reStart->SetActive(!value);
		goTitle->SetActive(!value);
	}

	audioText->SetActive(value);
	audioMaster->SetActive(value);
	audioSfx->SetActive(value);
	audioBgm->SetActive(value);
}

void ObjectOption::ShowOptionVisual(bool value)
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

		if (reStart)
		{
			goTitle->SetNextButton(optionEscape);
			optionEscape->SetNextButton(reStart);
		}
		else
		{
			optionVisual->SetNextButton(optionEscape);
			optionEscape->SetNextButton(optionAudio);
		}
	}

	isOptionSelect = value;

	optionAudio->SetActive(!value);
	optionVisual->SetActive(!value);
	if (reStart)
	{
		reStart->SetActive(!value);
		goTitle->SetActive(!value);
	}

	visualText->SetActive(value);
	visualBleeding->SetActive(value);
}
