#include "pch.h"
#include "Framework.h"

void Framework::Init(int width, int height, const std::string& name)
{
	srand(std::time(NULL));

	windowSize.x = width;
	windowSize.y = height;

	window.create(sf::VideoMode(windowSize.x, windowSize.y), name);
	preDraw.create(windowSize.x * 2, windowSize.y * 2);
	preDraw.setSmooth(true);
	shader.setUniform("texture", sf::Shader::CurrentTexture);
	shader.loadFromFile("resource/Shader/RGB.frag", sf::Shader::Fragment);

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
		preDraw.clear();
		SCENE_MGR.Draw(preDraw);
		preDraw.display();

		sf::Sprite postEffect(preDraw.getTexture());
		postEffect.setScale(0.5f, 0.5f);

		//후처리
		window.clear();
		if (useShader)
		{
			window.draw(postEffect, &shader);
		}
		else
		{
			window.draw(postEffect);
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
