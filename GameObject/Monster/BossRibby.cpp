#include "pch.h"
#include "BossRibby.h"
#include "SceneGame.h"

BossRibby::BossRibby(const std::string& name)
    :ObjectMonster(name)
{
}

void BossRibby::Init()
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

void BossRibby::Reset()
{
    ObjectMonster::Reset();
    scene = SCENE_MGR.GetCurrentScene();
    animator.SetTarget(&sprite);
    Intro();
}

void BossRibby::Update(float dt)
{
    ObjectMonster::Update(dt);
    if (hp == 0 )
    {
        Death();
    }
    switch (state)
    {
    case BossRibby::State::Idle:
        if (PatternTimer(dt))
        {
            SetState(State::Pattern1);
        }
        break;
    case BossRibby::State::Pattern1:
        if (hp <= maxHp * 0.70)
        {
            SetState(State::Roll);     //페이즈 변경
        }
        else
        {
            SetState(State::Shoot);    // Pattern1공격 shoot 실행
        }
        break;
    case BossRibby::State::Pattern2:
        if (hp <= maxHp * 0.30)
        {
            SetState(State::Pattern2);
        }
        else
        {
            SetState(State::ball);    // Pattern2공격 ball 실행
        }
        break;
    case BossRibby::State::Roll:           //2 패이즈를 위한 자리 이동
        break;
    }

    auto bounds = sprite.getGlobalBounds();
    float shrinkFactor = 0.1f;
    float widthReduction = bounds.width * (1 - shrinkFactor) / 2;
    float heightReduction = bounds.height * (1 - shrinkFactor) / 2;
    customBounds = sf::FloatRect(bounds.left + widthReduction, bounds.top, bounds.width * shrinkFactor, bounds.height);
}

void BossRibby::LateUpdate(float dt)
{
    ObjectMonster::LateUpdate(dt);

}

void BossRibby::Intro()
{
    SetState(State::None);
    animator.ClearEvent();
    animator.Play("animations/RibbyIntro.csv");
    animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossRibby::Idle, this));
}

void BossRibby::Idle()
{
}

void BossRibby::Roll()
{
}

void BossRibby::Shoot()
{
}

void BossRibby::ShootEnd()
{
}

void BossRibby::ball()
{
}

void BossRibby::ballEnd()
{
}

void BossRibby::Death()
{
}

void BossRibby::OnDie()
{
}

bool BossRibby::ShootTimer(float dt)
{
    shootTimer += dt;
    if (shootTimer >= shootInterval)
    {
        shootTimer = 0.f;
        return true;
    }
    return false;
}

bool BossRibby::PatternTimer(float dt)
{
    patternTimer += dt;
    if (patternTimer >= patternInterval)
    {
        patternTimer = 0.f;
        return true;
    }
    return false;
}

void BossRibby::SetState(State state)
{
    this->state = state;
    switch (state)
    {
    case BossRibby::State::Idle:
        animator.Play("animations/RibbyIdle.csv");
        preState = State::Idle;
        break;
    case BossRibby::State::Pattern1:
        break;
    case BossRibby::State::Pattern2:
        break;
    case BossRibby::State::Roll:
        break;
    case BossRibby::State::Shoot:
        break;
    case BossRibby::State::ball:
        break;
    case BossRibby::State::None:
        break;
    default:
        break;
    }
}

sf::FloatRect BossRibby::GetCustomBounds() const
{
    return customBounds;
}
