#pragma once
#include "Scene.h"

class SpriteGo;

class SceneTitle : public Scene
{
protected:
	int selectNum = -1;
	int selectButton = 1;

	sf::Music bgm;
	SpriteGo* bg;

public:
	SceneTitle(SceneIds id);
	virtual ~SceneTitle();
	SceneTitle() = default;
	SceneTitle(const SceneTitle&) = delete;
	SceneTitle(SceneTitle&&) = delete;
	SceneTitle& operator=(const SceneTitle&) = delete;
	SceneTitle& operator=(SceneTitle&&) = delete;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Draw(sf::RenderTexture& window) override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
};

