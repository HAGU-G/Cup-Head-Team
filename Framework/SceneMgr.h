#pragma once
#include "Singleton.h"

class Scene;

enum class SceneIds
{
	None = -1, SceneDev2, SceneDev, SceneDev1, Count,             //���� ���� �ؾ���
};

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::SceneDev2;
	SceneIds currentScene = startScene;
	SceneIds nextScene = SceneIds::None;
	bool isDeveloperMode = false;

	SceneMgr() = default;
	virtual ~SceneMgr();

public:
	void Init();
	void Release();

	void ChangeScene(SceneIds id);

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	bool GetDeveloperMode() { return isDeveloperMode; }

	bool Update(float dt);
	void LateUpdate(float dt);
	void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr(SceneMgr&&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;
	SceneMgr& operator=(SceneMgr&&) = delete;
};

#define SCENE_MGR (SceneMgr::Instance())