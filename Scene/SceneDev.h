#pragma once
#include "Scene.h"
class SceneDev : public Scene
{
protected:

public:
	SceneDev(SceneIds id);
	virtual ~SceneDev();
	SceneDev() = default;
	SceneDev(const SceneDev&) = delete;
	SceneDev(SceneDev&&) = delete;
	SceneDev& operator=(const SceneDev&) = delete;
	SceneDev& operator=(SceneDev&&) = delete;



	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Draw(sf::RenderWindow& window) override;
	void Update(float dt) override;
};

