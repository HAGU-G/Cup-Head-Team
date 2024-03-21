#pragma once
#include "SpriteGo.h"
class ObjectEffect : public SpriteGo
{
protected:
	float deadTimer = 0.f;
	float duration = 0.f;
	bool isDieByTime = false;
	
	sf::Vector2f direction;

	ObjectEffect(const std::string& name = "Effect");
public:
	virtual ~ObjectEffect() = default;
	ObjectEffect(const ObjectEffect&) = delete;
	ObjectEffect(ObjectEffect&&) = delete;
	ObjectEffect& operator=(const ObjectEffect&) = delete;
	ObjectEffect& operator=(ObjectEffect&&) = delete;

	void CreateInit(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene);

	void Init() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderTexture& window) override;

	void SetDirection(const sf::Vector2f direction);

	virtual void OnDie();
};

