#include "pch.h"
#include "Framework.h"

void Framework::Init(int width, int height, const std::string& name)
{
	srand(std::time(NULL));

	windowSize.x = width;
	windowSize.y = height;

	window.create(sf::VideoMode(windowSize.x, windowSize.y), name);
	LoadPostEffect();

	InputMgr::Init();
	SOUND_MGR.Init();
	SCENE_MGR.Init();
}

void Framework::Do()
{
	while (window.isOpen())
	{
		deltaTime = realDeltaTime = clock.restart();
		deltaTime *= timeScale;

		time += deltaTime;
		realTime += realDeltaTime;

		fixedDeltaTime += deltaTime;

		fpsTimer += realDeltaTime.asSeconds();
		fpsCount++;
		if (fpsTimer >= 1.f)
		{
			fpsTimer = 0.f;
			fps = fpsCount;
			fpsCount = 0;
		}

		InputMgr::Clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			InputMgr::UpdateEvent(event);
		}
		InputMgr::Update(GetDT());

		SOUND_MGR.Update(GetDT());

		if (SCENE_MGR.Update(GetDT()))
		{
			SCENE_MGR.LateUpdate(GetDT());
			float fdt = fixedDeltaTime.asSeconds();

			if (fdt > fixedUpdateTime)
			{
				SCENE_MGR.FixedUpdate(fdt);
				fixedDeltaTime = sf::Time::Zero;
			}
		}


		//1차 렌더링
		pass1.clear(sf::Color::Transparent);
		SCENE_MGR.Draw(pass1);
		pass1.display();

		sf::Sprite postEffect;
		postEffect.setScale(1.f / scale, 1.f / scale);

		//후처리
		window.clear(sf::Color::White);
		if (useShader)
		{
			pass2.clear(sf::Color::Transparent);
			Pass2(GetDT());
			pass2.draw(sf::Sprite(pass1.getTexture()),renderStates);
			pass2.display();
			postEffect.setTexture(pass2.getTexture());
			window.draw(postEffect,&smooth);
		}
		else
		{
			postEffect.setTexture(pass1.getTexture());
			window.draw(postEffect, &smooth);
		}
		window.display();
	}
}

void Framework::Release()
{
	SOUND_MGR.Release();
	SCENE_MGR.Release();

	RES_MGR_TEXTURE.UnloadAll();
	RES_MGR_FONT.UnloadAll();
	RES_MGR_SOUND_BUFFER.UnloadAll();
}

void Framework::LoadPostEffect()
{
	pass1.create(windowSize.x * scale, windowSize.y * scale);
	pass1.setSmooth(true);
	pass2.create(pass1.getSize().x, pass1.getSize().y);
	pass2.setSmooth(true);

	bleeding.loadFromFile("resource/Shader/Bleeding.frag", sf::Shader::Fragment);
	bleeding.setUniform("texture", sf::Shader::CurrentTexture);
	SetBleedingValue(bleedingValue);

	smooth.loadFromFile("resource/Shader/Smooth.frag", sf::Shader::Fragment);
	smooth.setUniform("texture", sf::Shader::CurrentTexture);

	renderStates.blendMode = sf::BlendMode(sf::BlendMode::DstAlpha,sf::BlendMode::One, sf::BlendMode::Min);
	renderStates.shader = &bleeding;

	float filmScale = std::max(pass1.getSize().x / 1024.f, pass1.getSize().y / 512.f);
	filmGrain.setScale(filmScale, filmScale);
	filmGrain.setPosition(sf::Vector2f(pass1.getSize()) * 0.5f);
	filmGrain.setOrigin(512, 256);

	for (int i = 0; i <= 126; i++)
	{
		if (i >= 100)
		{
			middle = "0" + std::to_string(i);
		}
		else if (i >= 10)
		{
			middle = "00" + std::to_string(i);
		}
		else
		{
			middle = "000" + std::to_string(i);
		}
		RES_MGR_TEXTURE.Load(left + middle + right);
	}
}

void Framework::Pass2(float dt)
{
	static int flimCount = 0;
	filmTimer += dt;
	if (filmTimer >= filmInterval)
	{
		filmTimer = 0.f;
		flimCount++;
		if (flimCount >= 33)
		{
			flimCount = 0;
			filmDirection = 1 + -2 * Utils::RandomRange(0, 2);
		}
		filmNum += filmDirection;
		if (filmNum > 126) { filmNum = 0; }
		if (filmNum < 0) { filmNum = 126; }
	}
	if (filmNum >= 100)
	{
		middle = "0" + std::to_string(filmNum);
	}
	else if (filmNum >= 10)
	{
		middle = "00" + std::to_string(filmNum);
	}
	else
	{
		middle = "000" + std::to_string(filmNum);
	}
	filmGrain.setTexture(RES_MGR_TEXTURE.Get(left + middle + right));

	pass2.draw(filmGrain);
}

inline void Framework::SetBleedingValue(float value)
{
	bleedingValue = Utils::Clamp(value, 0.f, 1.f);
	bleeding.setUniform("bleedingValue", bleedingValue);
}
