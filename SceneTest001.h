#pragma once
#include "Scene.h"
class SceneTest001 : public Scene
{
protected:

public:
	explicit SceneTest001(const std::string& name);
	SceneTest001(const SceneTest001&) = delete;
	SceneTest001(SceneTest001&&) = delete;
	~SceneTest001() override;
	SceneTest001& operator=(const SceneTest001&) = delete;
	SceneTest001& operator=(SceneTest001&&) = delete;

	void AddResource() override; //empty
	void Init() override;
	void PreUpdate(float timeDelta, float timeScale) override;	//����
	void Update(float timeDelta, float timeScale) override;		//���� ������Ʈ
	void PostUpdate(float timeDelta, float timeScale) override;	//����
	void Draw(sf::RenderWindow& window) override;
	void Reset() override;
	void Release() override;
};

