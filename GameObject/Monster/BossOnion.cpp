#include "pch.h"
#include "BossOnion.h"

BossOnion::BossOnion(const std::string& name)
    :ObjectMonster(name)
{
}

void BossOnion::Init()
{
    ObjectMonster::Init();
}

void BossOnion::Reset()
{
    ObjectMonster::Reset();
}

void BossOnion::Update(float dt)
{
    ObjectMonster::Update(dt);
}

void BossOnion::LateUpdate(float dt)
{
    ObjectMonster::LateUpdate(dt);
}

void BossOnion::Intro()
{
}

void BossOnion::Idle()
{
}

void BossOnion::Shoot()
{
}

void BossOnion::ShootEnd()
{
}

void BossOnion::Death()
{
}

void BossOnion::Leave()
{
}

void BossOnion::OnDie()
{
    scene->RemoveGo(this);
}

bool BossOnion::PatternTimer(float dt)
{
    patternTimer += dt;
    if (patternTimer >= patternInterval)
    {
        patternTimer = 0.f;
        return true;
    }
    return false;
}

void BossOnion::SetState(State state)
{

}

bool BossOnion::CollisionCheck()
{
    return true;
}
