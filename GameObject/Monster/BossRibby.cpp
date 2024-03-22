#include "pch.h"
#include "BossRibby.h"
#include "SceneGame.h"

Ribby::Ribby(const std::string& name)
    :ObjectMonster(name)
{
}

void Ribby::Init()
{
    ObjectMonster::Init();

    RES_MGR_TEXTURE.Load("resource/RibbyDeath.png");
    RES_MGR_TEXTURE.Load("resource/RibbyIdle.png");
    RES_MGR_TEXTURE.Load("resource/RibbyIntro.png");
    RES_MGR_TEXTURE.Load("resource/RibbyRoll.png");
    RES_MGR_TEXTURE.Load("resource/RibbyShoot.png");
    RES_MGR_TEXTURE.Load("resource/RibbyBall.png");

    hasHitBox = true;
}

void Ribby::Reset()
{
    ObjectMonster::Reset();
    scene = SCENE_MGR.GetCurrentScene();
    animator.SetTarget(&sprite);
    Intro();
}

void Ribby::Update(float dt)
{
    ObjectMonster::Update(dt);
    if (hp == 0 )
    {
        Death();
    }
    switch (state)
    {
    case Ribby::State::Idle:
        if (PatternTimer(dt))
        {
            SetState(State::Pattern1);
        }
        break;
    case Ribby::State::Pattern1:
        if (hp <= maxHp * 0.70)
        {
            SetState(State::Roll);     //페이즈 변경
        }
        else
        {
            SetState(State::Shoot);    // Pattern1공격 shoot 실행
        }
        break;
    case Ribby::State::Pattern2:
        if (hp <= maxHp * 0.30)
        {
            SetState(State::Pattern2);
        }
        else
        {
            SetState(State::ball);    // Pattern2공격 ball 실행
        }
        break;
    case Ribby::State::Roll:           //2 패이즈를 위한 자리 이동
        break;
    }
}

void Ribby::LateUpdate(float dt)
{
    ObjectMonster::LateUpdate(dt);

}

void Ribby::Intro()
{
}

void Ribby::Idle()
{
}

void Ribby::Roll()
{
}

void Ribby::Shoot()
{
}

void Ribby::ShootEnd()
{
}

void Ribby::ball()
{
}

void Ribby::ballEnd()
{
}

void Ribby::Death()
{
}

void Ribby::OnDie()
{
}

bool Ribby::ShootTimer(float dt)
{
    shootTimer += dt;
    if (shootTimer >= shootInterval)
    {
        shootTimer = 0.f;
        return true;
    }
    return false;
}

bool Ribby::PatternTimer(float dt)
{
    patternTimer += dt;
    if (patternTimer >= patternInterval)
    {
        patternTimer = 0.f;
        return true;
    }
    return false;
}

void Ribby::SetState(State state)
{
    this->state = state;
    switch (state)
    {
    case Ribby::State::Idle:
        break;
    case Ribby::State::Pattern1:
        break;
    case Ribby::State::Pattern2:
        break;
    case Ribby::State::Roll:
        break;
    case Ribby::State::Shoot:
        break;
    case Ribby::State::ball:
        break;
    case Ribby::State::None:
        break;
    default:
        break;
    }
}

sf::FloatRect Ribby::GetCustomBounds() const
{
    return customBounds;
}
