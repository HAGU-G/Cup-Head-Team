#include "pch.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& name)
	: GameObject(name)
{
}

sf::FloatRect SpriteGo::GetLocalBounds()
{
	return sprite.getLocalBounds();
}

sf::FloatRect SpriteGo::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

void SpriteGo::SetTexture(const std::string& textureId, bool resetRect)
{
	this->textureId = textureId;
	sprite.setTexture(RES_MGR_TEXTURE.Get(textureId), resetRect);
	size = sf::Vector2f(sprite.getTextureRect().getSize());
}

void SpriteGo::SetPosition(const sf::Vector2f& pos)
{
	//GameObject::SetPosition(pos);
	position = pos;
	sprite.setPosition(pos);
}

void SpriteGo::Translate(const sf::Vector2f& delta)
{
	position += delta;
	SetPosition(position);
}

void SpriteGo::SetRotation(const float r)
{
	rotation = r;
	sprite.setRotation(r);
}

void SpriteGo::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
	{
		preset = Origins::TL;
	}
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, originPreset);
}

void SpriteGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(newOrigin);
}

void SpriteGo::SetScale(const sf::Vector2f& s)
{
	sf::Vector2f spriteScale = scale = s;
	if (isFlipX)
	{
		spriteScale.x = -scale.x;
	}
	if (isFlipY)
	{
		spriteScale.y = -scale.y;
	}
	sprite.setScale(spriteScale);
}

void SpriteGo::SetFlipX(bool filp)
{
	if (isFlipX == filp)
		return;

	isFlipX = filp;
	SetScale(scale);
}

void SpriteGo::SetFlipY(bool filp)
{
	if (isFlipY == filp)
		return;

	isFlipY = filp;
	SetScale(scale);
}

void SpriteGo::Update(float dt)
{
	GameObject::Update(dt);
	animator.Update(dt);
}

void SpriteGo::Reset()
{

}

void SpriteGo::Draw(sf::RenderTexture& window)
{
	if (useRenderStates)
	{
		window.draw(sprite, renderStates);
	}
	else
	{
		window.draw(sprite);
	}

	if (hasHitBox && SCENE_MGR.GetDeveloperMode())
	{
		sf::RectangleShape globalHitBox;
		sf::FloatRect globalBound = sprite.getGlobalBounds();

		sf::RectangleShape imageBox;

		sf::RectangleShape localHitBox;
		sf::FloatRect localBound = sprite.getLocalBounds();

		globalHitBox.setPosition(globalBound.left, globalBound.top);
		globalHitBox.setSize({ globalBound.width, globalBound.height });
		globalHitBox.setOutlineColor(sf::Color::Red);
		globalHitBox.setOutlineThickness(1.f);
		globalHitBox.setFillColor(sf::Color::Transparent);

		window.draw(globalHitBox);

	}
}
