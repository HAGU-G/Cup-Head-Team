#pragma once
#include "Scene.h"
#include "Animator.h"
class SceneDev : public Scene
{
protected:
	Animator animator;
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

	void Draw(sf::RenderTexture& window) override;
	void Update(float dt) override;
};

