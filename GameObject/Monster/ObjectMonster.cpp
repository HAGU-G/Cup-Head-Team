#include "pch.h"
#include "ObjectMonster.h"
#include "Effect/EffectBossExplosion.h"

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

void ObjectMonster::SetCustomBounds(float ratioX, float ratioY, Origins origin)
{
	customBounds.setSize({ sprite.getGlobalBounds().getSize().x * ratioX, sprite.getGlobalBounds().getSize().y * ratioY });
	Utils::SetOrigin(customBounds, origin);
}


void ObjectMonster::BossDieEffect(float dt)
{
	static float timer = 0.f;
	static float timeLimit = 0.3f;
	timer += dt;
	if (timer >= timeLimit || dt < 0.f)
	{
		timer = 0.f;
		auto bound = sprite.getGlobalBounds();
		EffectBossExplosion::Create({ Utils::RandomRange(bound.left,bound.left + bound.width),Utils::RandomRange(bound.top,bound.top + bound.height) },
			Utils::RandomInUnitCircle(), scene);
	}
}
