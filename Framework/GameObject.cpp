#include "pch.h"
#include "GameObject.h"


size_t GameObject::currentCount = 0;
size_t GameObject::totalCount = 0;

void GameObject::Setkey(const std::string& loadedKey)
{
	key = loadedKey;
}

GameObject::GameObject(Scene* scene, const std::string& name, GAME_OBJECT_TYPE objectType)
	:scene(scene), key(name), gameObjectType(objectType)
{
	currentCount++;
	totalCount++;
}

GameObject::~GameObject()
{
	currentCount--;
	Release();
}

bool GameObject::AddTag(GAME_OBJECT_TAG tag)
{
	if (std::find(gameObjectTagList.begin(), gameObjectTagList.end(), tag) == gameObjectTagList.end())
	{
		gameObjectTagList.push_back(tag);
		return true;
	}
	return false;
}

bool GameObject::RemoveTag(GAME_OBJECT_TAG tag)
{
	if (std::find(gameObjectTagList.begin(), gameObjectTagList.end(), tag) != gameObjectTagList.end())
	{
		gameObjectTagList.remove(tag);
		return true;
	}
	return false;
}



void GameObject::Init()
{
}

void GameObject::PreUpdate(float timeDelta, float timeScale)
{
}

void GameObject::Update(float timeDelta, float timeScale)
{
}

void GameObject::PostUpdate(float timeDelta, float timeScale)
{
}

void GameObject::Draw(sf::RenderWindow& window)
{
}

void GameObject::Reset()
{
}

void GameObject::Release()
{
	scene = nullptr;
}

void GameObject::SetScene(Scene* scene)
{
	this->scene = scene;
}

void GameObject::SetPositionX(float x)
{
	SetPosition({ x,position.y });
}

void GameObject::SetPositionY(float y)
{
	SetPosition({ position.x,y });
}

void GameObject::SetPosition(const sf::Vector2f& position)
{
	this->position = position;
}

void GameObject::SetDrawDeep(float value)
{
	drawDeep = value;
}

void GameObject::SetActive(bool value)
{
	isActive = value;
}

size_t GameObject::GetObjectsCount()
{
	return currentCount;
}

size_t GameObject::GetObjectsTotalCount()
{
	return totalCount;
}

std::string GameObject::GetKey() const
{
	return key;
}

const GAME_OBJECT_TYPE& GameObject::GetGameObjectType() const
{
	return gameObjectType;
}

const std::list<GAME_OBJECT_TAG>& GameObject::GetGameObjectTagList() const
{
	return gameObjectTagList;
}

const float &GameObject::GetDrawDeep() const
{
	return drawDeep;
}

const sf::Vector2f& GameObject::GetPosition() const
{
	return position;
}

