#include "pch.h"
#include "Scene.h"
#include "Framework.h"


size_t Scene::currentCount = 0;
size_t Scene::totalCount = 0;

Scene::Scene(const std::string& name)
	:name(name)
{
	currentCount++;
	totalCount++;
}

Scene::~Scene()
{
	currentCount--;
}

void Scene::AddResource()
{
}

void Scene::Init()
{
	view.setSize(Framework::GetDefaultSize().x, Framework::GetDefaultSize().x / Framework::GetWindowRatio().x * Framework::GetWindowRatio().y);
	view.setCenter(view.getSize() * 0.5f);
	resetView = view;
}

void Scene::PreUpdate(float timeDelta, float timeScale)
{
	mousePosWorld = Framework::GetWindow().mapPixelToCoords(Framework::GetMousePosWindow(), view);
	for (auto& pair : gameObjectList)
	{
		if (pair.second->IsActive())
			pair.second->PreUpdate(timeDelta, timeScale);
	}
}

void Scene::Update(float timeDelta, float timeScale)
{
	for (auto& pair : gameObjectList)
	{
		if (pair.second->IsActive())
			pair.second->Update(timeDelta, timeScale);
	}
}
void Scene::PostUpdate(float timeDelta, float timeScale)
{
	for (auto& pair : gameObjectList)
	{
		if (pair.second->IsActive())
			pair.second->PostUpdate(timeDelta, timeScale);
	}


	//delete
	while (!deleteDeque.empty())
	{
		auto it = gameObjectList.find(deleteDeque.front());
		if (it != gameObjectList.end())
		{
			auto drawIt = drawList.begin();
			while (drawIt != drawList.end())
			{
				if (drawIt->first == it->first)
				{
					drawIt = drawList.erase(drawIt);
					break;
				}
				else
				{
					drawIt++;
				}
			}
			gameObjectList.erase(it);
		}
		deleteDeque.pop_front();
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	if (doDrawLayerSort)
		SortDrawList();
	const sf::View& preView = window.getView();
	window.setView(view);
	for (auto& pair : drawList)
	{
		if (pair.second.lock()->IsActive() && pair.second.lock()->IsShow())
			pair.second.lock()->Draw(window);
	}
	window.setView(preView);
}

void Scene::Reset()
{
	for (auto& pair : gameObjectList)
	{
		pair.second->Reset();
	}
}

void Scene::Release()
{
	for (auto& pair : gameObjectList)
	{
		pair.second->Release();
	}
	gameObjectList.clear();
	drawList.clear();
}

void Scene::Enter()
{
}

void Scene::Exit()
{
}

float Scene::GetTimeScale() const
{
	if (useGlobalTimeScale)
	{
		return Framework::GetGlobalTimeScale();
	}
	else
	{
		return timeScale;
	}
}

size_t Scene::GetScenesCount()
{
	return currentCount;
}

size_t Scene::GetScenesTotalCount()
{
	return totalCount;
}

const std::string& Scene::GetSceneName() const
{
	return name;
}

const std::unordered_map<std::string, std::shared_ptr<GameObject>>& Scene::GetObjects() const
{
	return gameObjectList;
}


const std::shared_ptr<GameObject>& Scene::AddObject(const std::shared_ptr<GameObject>& object)
{
	auto it = gameObjectList.insert(std::make_pair(object->GetKey(), object));

	if (!it.second)
		return std::shared_ptr<GameObject>(nullptr);

	if (drawList.empty())
	{
		drawList.push_back(*it.first);
		return object;
	}
	else
	{
		auto drawIt = drawList.begin();
		while (drawIt != drawList.end())
		{
			if (it.first->second->GetDrawDeep() > drawIt->second.lock()->GetDrawDeep())
			{
				drawList.insert(drawIt, *it.first);
				return object;
			}
			else
			{
				drawIt++;
			}
		}
		drawList.push_back(*it.first);
		return object;
	}
}

void Scene::SortDrawList()
{
	drawList.sort(
		[](std::pair<std::string, std::weak_ptr<GameObject>>& left,
			std::pair<std::string, std::weak_ptr<GameObject>>& right)
		{
			return left.second.lock()->GetDrawDeep() > right.second.lock()->GetDrawDeep();
		});
}

const std::shared_ptr<GameObject>& Scene::GetObject(const std::string& key) const
{
	auto it = gameObjectList.find(key);
	if (it != gameObjectList.end())
		return it->second;
	return std::shared_ptr<GameObject>(nullptr);
}
const std::shared_ptr<GameObject>& Scene::GetObject(std::weak_ptr<GameObject> object) const
{
	return GetObject(object.lock()->GetKey());
}

void Scene::DeleteObject(const std::string& key)
{
	deleteDeque.push_back(key);
}


