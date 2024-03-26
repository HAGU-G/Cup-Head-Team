#include "pch.h"
#include "ObjectMonster.h"

ObjectMonster::ObjectMonster(const std::string& name)
	:SpriteGo(name)
{
}

void ObjectMonster::Init()
{
	hasHitBox = true;
	shaderHit.setUniform("texture", sf::Shader::CurrentTexture);
	shaderHit.loadFromFile("resource/Shader/Hit.frag", sf::Shader::Fragment);
	renderStates.shader = &shaderHit;
}

void ObjectMonster::Update(float dt)
{
	SpriteGo::Update(dt);
	if (useRenderStates)
	{
		hitEffectTimer += dt;
		if (hitEffectTimer >= hitEffectDuration)
		{
			hitEffectTimer = 0.f;
			useRenderStates = false;
		}
	}
}

void ObjectMonster::Reset()
{
	hp = maxHp;
}

bool ObjectMonster::OnDamage(int damage)
{
	if (hp > 0)
	{
		useRenderStates = true;
		hp = (hp - damage >= 0) ? (hp - damage) : 0;
		return true;
	}
	return false;
}