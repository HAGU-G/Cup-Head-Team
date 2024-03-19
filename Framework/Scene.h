#pragma once
#ifndef SCENE_H
#define SCENE_H
#include "SceneManager.h"

class GameObject;

class Scene
{
private:
	static size_t currentCount;
	static size_t totalCount;

	const std::string name;

protected:
	std::unordered_map<std::string, GameObject*> gameObjects;
	std::list<std::pair<std::string, GameObject*>> drawList;
	std::deque<std::string> deleteDeque;

	float timeScale = 1.f;
	bool useGlobalTimeScale = true;
	bool doDrawLayerSort = false;
	sf::View view;
	sf::View resetView;
	sf::Vector2f mousePosWorld;
	sf::Vector2f worldCenter = { 0.f, 0.f };

	explicit Scene(const std::string& name);
	Scene(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene& operator=(Scene&&) = delete;

public:
	virtual ~Scene();

	virtual void AddResource();//empty
	virtual void Init();
	virtual void PreUpdate(float timeDelta, float timeScale);	//생성
	virtual void Update(float timeDelta, float timeScale);		//메인 업데이트
	virtual void PostUpdate(float timeDelta, float timeScale);	//삭제
	virtual void Draw(sf::RenderWindow& window);
	virtual void Reset();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	//Set
	void UseGlobalTimeScale(bool value) { useGlobalTimeScale = value; }
	void SetTimeScale(float value) { timeScale = value; }
	inline void SetDoDrawlayerSort(bool value) { doDrawLayerSort = value; }

	//Get
	static size_t GetScenesCount();
	static size_t GetScenesTotalCount();
	const std::string& GetSceneName() const;
	float GetTimeScale() const;
	inline const sf::View& GetView() const { return view; }
	inline const sf::View& GetResetView() const { return resetView; }
	inline const sf::Vector2f& GetMousePosWorld() const { return mousePosWorld; }

	//gameObjectsList
	const GameObject* AddGo(GameObject* object);
	const GameObject* FindGo(const std::string& key) const;
	void DeleteGo(const std::string& key);

	//drawList
	virtual void SortDrawList();
};



#endif // !SCENE_H