#include "pch.h"
#include "Framework.h"
#include <SceneManager.h>

sf::RenderWindow Framework::window;
sf::RenderWindow Framework::debugWindow;
sf::VertexArray Framework::fpsGraph(sf::LinesStrip, 300);

WINDOW_MODE Framework::currentMode = WINDOW_MODE::WINDOW;
sf::Vector2f Framework::defaultSize = { 1920, 1080 };
sf::Vector2u Framework::currentSize = sf::Vector2u(Framework::defaultSize);
sf::Vector2f Framework::windowRatio = Framework::defaultSize;

sf::Clock Framework::globalClock;
float Framework::globalTimeDelta = 0.f;
float Framework::globalTimeScale = 1.f;
float Framework::globalTimer = 0.f;

sf::Vector2i  Framework::mousePosScreen;
sf::Vector2i  Framework::mousePosWindow;

std::random_device* Framework::rd = nullptr; // randomDevice
std::mt19937* Framework::rg = nullptr; //randomGenerator

std::string Framework::lastGameName = "";

bool Framework::doDebug = false;
bool Framework::canDebug = true;


void Framework::Init()
{
	/////////////////////////////
	// 
	//       윈도우
	// 
	/////////////////////////////
	currentSize = {sf::VideoMode::getDesktopMode().width ,sf::VideoMode::getDesktopMode().height };
	//currentSize = { 1920,1080 };
	windowRatio = sf::Vector2f(currentSize);
	window.create(sf::VideoMode(currentSize.x, currentSize.y), "Cities2D", sf::Style::Close);
	currentMode = WINDOW_MODE::WINDOW;
	SetWindowSize(1440);
	SetWindowPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - currentSize.x) / 2,
		(sf::VideoMode::getDesktopMode().height - currentSize.y) / 2)); //스크린 중앙에 위치하도록
	//window.setFramerateLimit(20);
	window.display();

	/////////////////////////////
	//	
	//       디버그 윈도우
	// 
	/////////////////////////////
	debugWindow.create(sf::VideoMode(200, 400), "Cities2D : Debug", sf::Style::Close);
	debugWindow.setPosition(sf::Vector2i(window.getPosition().x - debugWindow.getSize().x, window.getPosition().y));
	debugWindow.display();
	debugWindow.setVisible(false);
	window.requestFocus(); //메인 윈도우 포커싱
	for (int i = 0; i <= fpsGraph.getVertexCount() - 4; i++)
	{
		fpsGraph[i + 2].position = { 1.f + i * 198.f / (fpsGraph.getVertexCount() - 4) ,1.f };
	}

	/////////////////////////////
	// 
	//       씬
	// 
	/////////////////////////////
	AddScene();


	/////////////////////////////
	// 
	//       Manager
	// 
	/////////////////////////////
	SoundManager::SoundInit();

	/////////////////////////////
	// 
	//       초기화 완료 작업
	// 
	/////////////////////////////	
	globalClock.restart();
}

void Framework::MainLoop()
{
	while (window.isOpen())
	{
		mousePosWindow = sf::Mouse::getPosition(window);

		globalTimeDelta = globalClock.restart().asSeconds();
		globalTimer += globalTimeDelta;

		/////////////////////////////
		// 
		//       이벤트 루프
		// 
		/////////////////////////////
		InputManager::KeyUpdate(globalTimeDelta, globalTimeScale);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				debugWindow.close();
				window.close();
			}
			InputManager::KeyEventUpdate(event);
		}

		/////////////////////////////
		// 
		//       업데이트
		// 
		/////////////////////////////
		SoundManager::SoundUpdate(globalTimeDelta, globalTimeScale);
		SceneManager::PreUpdate(globalTimeDelta);
		SceneManager::Update(globalTimeDelta);
		SceneManager::PostUpdate(globalTimeDelta);

		/////////////////////////////
		// 
		//       렌더링
		// 
		/////////////////////////////
		window.clear();
		SceneManager::Draw(window);
		window.display();

		/////////////////////////////
		// 
		//       디버그 윈도우
		// 
		/////////////////////////////
		if (InputManager::IsKeyDown(sf::Keyboard::F3) && canDebug)
		{
			doDebug = !doDebug;
			debugWindow.setVisible(doDebug);
			window.requestFocus();
		}
		if (InputManager::IsKeyDown(sf::Keyboard::Enter) && InputManager::IsKeyPress(sf::Keyboard::LAlt))
		{
			switch (currentMode)
			{
			case WINDOW_MODE::WINDOW:
				doDebug = false;
				debugWindow.setVisible(doDebug);
				currentSize = { sf::VideoMode::getDesktopMode().width ,sf::VideoMode::getDesktopMode().height };
				window.create(sf::VideoMode(currentSize.x, currentSize.y), "Cities2D", sf::Style::None);
				currentMode = WINDOW_MODE::BORDERLESS;
				break;
			case WINDOW_MODE::BORDERLESS:
				window.create(sf::VideoMode(currentSize.x, currentSize.y), "Cities2D", sf::Style::Close);
				currentMode = WINDOW_MODE::WINDOW;
				SetWindowSize(1440);
				SetWindowPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - currentSize.x) / 2,
					(sf::VideoMode::getDesktopMode().height - currentSize.y) / 2));
				break;
			}

		}

		DebugUpdate();
	}
}

void Framework::Release()
{
	while (debugWindow.isOpen()) {}
	SceneManager::Release();
	SoundManager::SoundRelease();
}

void Framework::SetWindowSize(unsigned int x)
{
	currentSize.x = x;
	currentSize.y = x / windowRatio.x * windowRatio.y;
	window.setSize(currentSize);
}
void Framework::SetWindowRatio(unsigned int x, unsigned int y)
{
	windowRatio.x = x;
	windowRatio.y = y;
	SetWindowSize(currentSize.x);
}
void Framework::SetWindowPosition(sf::Vector2i position)
{
	window.setPosition(position);
}

void Framework::AddScene()
{
	//SceneManager::Add(std::make_shared<SceneTitle>("SceneTitle"));
	//SceneManager::Add(std::make_shared<SceneGame>("SceneGame"));
	//SceneManager::Add(std::make_shared<SceneGameUI>("SceneGameUI"));
	//SceneManager::Add(std::make_shared<SceneMenu>("SceneMenu"));
}








/////////////////////////////
// 
//       디버그 윈도우
// 
/////////////////////////////
void Framework::DebugUpdate()
{

	sf::Event event;
	while (debugWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			debugWindow.close();
	}

	if (!doDebug)
		return;
	//텍스트
	sf::Text text;
	int fontSize = 24;
	float graphRatio = fontSize / 165.f;
	float infoY = 0.f;
	text.setCharacterSize(fontSize);
	text.setFont(SFGM_FONT.Load("resource/font/ROKAF Sans Medium.ttf"));

	//렌더링
	debugWindow.clear();
	{
		fpsGraph[1].position = sf::Vector2f(1.f, fontSize);
		fpsGraph[1].color = sf::Color::Green;
		fpsGraph[0].position = sf::Vector2f(199.f, fontSize);
		fpsGraph[0].color = sf::Color::Green;
		fpsGraph[fpsGraph.getVertexCount() - 1].position = fpsGraph[0].position;
		fpsGraph[fpsGraph.getVertexCount() - 1].color = sf::Color::Green;
		fpsGraph[fpsGraph.getVertexCount() - 2].position = sf::Vector2f(199.f, fontSize - (1.f / globalTimeDelta) * graphRatio);
		if (fpsGraph[fpsGraph.getVertexCount() - 2].position.y >= fontSize - 30.f * graphRatio)
			fpsGraph[fpsGraph.getVertexCount() - 2].color = sf::Color::Red;
		else if (fpsGraph[fpsGraph.getVertexCount() - 2].position.y >= fontSize - 60.f * graphRatio)
			fpsGraph[fpsGraph.getVertexCount() - 2].color = sf::Color::Yellow;
		else
			fpsGraph[fpsGraph.getVertexCount() - 2].color = sf::Color::Green;
		debugWindow.draw(fpsGraph);
		for (int i = 0; i <= fpsGraph.getVertexCount() - 5; i++)
		{
			fpsGraph[i + 2].position = { 1.f + i * 198.f / (fpsGraph.getVertexCount() - 4) ,fpsGraph[i + 3].position.y };
			if (fpsGraph[i + 2].position.y >= fontSize - 30.f * graphRatio)
				fpsGraph[i + 2].color = sf::Color::Red;
			else if (fpsGraph[i + 2].position.y >= fontSize - 60.f * graphRatio)
				fpsGraph[i + 2].color = sf::Color::Yellow;
			else
				fpsGraph[i + 2].color = sf::Color::Green;
		}

	}
	infoY += fontSize * 1;
	text.setPosition(0.f, infoY);

	text.setFillColor(sf::Color::Green);
	text.setString(std::to_string(1 / globalTimeDelta));
	debugWindow.draw(text);
	infoY += fontSize * 1;
	text.setPosition(0.f, infoY);

	text.setFillColor(sf::Color::White);
	text.setString(
	"[WorldPos]\n"
	);
	debugWindow.draw(text);
	infoY += fontSize * 4;
	text.setPosition(0.f, infoY);

	text.setString(
		"[GridPos]\n"
	);
	debugWindow.draw(text);
	infoY += fontSize * 4;
	text.setPosition(0.f, infoY);

	text.setString(
		"[ObjectCount]\n"
	);
	debugWindow.draw(text);
	infoY += fontSize * 4;
	text.setPosition(0.f, infoY);

	debugWindow.display();
}

void Framework::Exit()
{
	debugWindow.close();
	window.close();
}

void Framework::SetCanDebug(bool value)
{
	canDebug = value;
}

float Framework::RandomRange(float a, float b)
{
	std::uniform_real_distribution<float> urf(std::min(a, b), std::max(a, b)); //uniformed random float
	return urf((*rg));
}

int Framework::RandomRange(int a, int b)
{
	std::uniform_int_distribution<int> uri(std::min(a, b), std::max(a, b)); //uniformed random float
	return uri((*rg));
}

