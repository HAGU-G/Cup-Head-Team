#pragma once
#include "Singleton.h"
#include <string>

// 1. 초기화 / 메인루프 / 정리
// 2. 시간 관련 기능 / 윈도우 정보
// 3. ...Mgr 

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:
	Framework() = default;
	virtual ~Framework() = default;

	sf::RenderWindow window;
	sf::Vector2i windowSize;
	sf::Vector2f stageViewSize = { 1280.f / 1.1f,720.f / 1.1f };
	sf::Vector2f stageViewCenter = { 0.f, -250.f };
	sf::RenderTexture pass1;
	sf::RenderTexture pass2;
	sf::RenderStates renderStates;
	float scale = 2.f;
	sf::Shader bleeding;
	sf::Shader smooth;

	sf::Sprite filmGrain;
	int filmNum = -1;
	int filmDirection = 1;
	float filmInterval = 0.05f;
	float filmTimer = filmInterval;
	std::string left = "resource/Film/cuphead_screen_fx_";
	std::string middle;
	std::string right = ".png";

	float fixedUpdateTime = 1.f / 50.f;

	bool useShader = true;

	sf::Clock clock;
	float timeScale = 1.f;

	sf::Time realTime; // 게임 시작부터 경과 시간
	sf::Time time; // 게임 시작부터 경과 시간 (timeScale 적용된...)

	sf::Time realDeltaTime;
	sf::Time deltaTime;

	sf::Time fixedDeltaTime;

	float fpsTimer = 0.f;
	int fpsCount = 0;
	int fps = 0;

public:
	sf::RenderTexture& GetWindow() { return pass1; }	// !!
	sf::RenderWindow& GetWindowReal() { return window; }
	const sf::Vector2i& GetWindowSize() const { return windowSize; }
	const sf::Vector2f& GetStageViewSize() const { return stageViewSize; }
	const sf::Vector2f& GetStageViewCenter() const { return stageViewCenter; }

	float GetRealTime() const { return realTime.asSeconds(); }
	float GetTime() const { return time.asSeconds(); }
	float GetRealDT() const { return realDeltaTime.asSeconds(); }
	float GetDT() const { return deltaTime.asSeconds(); }

	float GetTimeScale() const { return timeScale; }
	void SetTimeScale(float scale) { timeScale = scale; }

	int GetFps() const { return fps; }

	void SetUseShader(bool value) { useShader = value; }

	virtual void Init(int width, int height, const std::string& name = "Game");
	virtual void Do();
	virtual void Release();
	
	void LoadPostEffect();
	void Pass2(float dt);
};

#define FRAMEWORK (Singleton<Framework>::Instance())

