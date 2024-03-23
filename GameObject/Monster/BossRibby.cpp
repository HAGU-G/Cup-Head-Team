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
    RES_MGR_TEXTURE.Load("resource/RibbyRolling.png");
    RES_MGR_TEXTURE.Load("resource/RibbyShoot.png");
    RES_MGR_TEXTURE.Load("resource/RibbyShooting.png");
    RES_MGR_TEXTURE.Load("resource/RibbyShootEnd.png");
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

    if (isMovingRight)
    {
        MoveToRight(dt);
    }

    if (isMovingLeft)
    {
        MoveToLeft(dt);
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
        if (hp <= maxHp * 0.60 && state != State::Roll)
        {
            SetState(State::Roll); 
        }
        if (state == State::Pattern1 && shootCount >= 7)
        {
            shootCount = 0;
            SetState(State::Idle);
        }

        break;
    case BossRibby::State::Pattern2:
        Intro2();
        if (hp <= maxHp * 0.30 && state != State::Roll)
        {
            SetState(State::Roll);
        }
        break;
    case BossRibby::State::Roll:
        //if (/*왼쪽 화면으로 나가면*/)
        //{
        //    SetState(State::Pattern2);
        //}
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
    if (InputMgr::GetKeyDown(sf::Keyboard::Space))
    {
        SetState(State::Pattern2);
    }
}

void BossRibby::Intro()
{
    SetState(State::None);
    animator.ClearEvent();
    animator.Play("animations/RibbyIntro.csv");
    animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossRibby::Idle, this));
}

void BossRibby::Intro2()
{
    SetState(State::None);
    animator.ClearEvent();
    animator.Play("animations/RibbyIntro2.csv");
    animator.AddEvent(animator.GetCurrentCilpId(), animator.GetCurrentClip()->GetTotalFrame(), std::bind(&BossRibby::Idle, this));
}

void BossRibby::Idle()
{
    SetState(State::Idle);
}

void BossRibby::Roll()
{
    SetState(State::Roll);
}

void BossRibby::MoveToLeft(float dt)
{
    sf::Vector2f newPosition = position - sf::Vector2f(moveSpeed * dt, 0);
    SetPosition(newPosition);
}

void BossRibby::MoveToRight(float dt)
{
    sf::Vector2f newPosition = position + sf::Vector2f(moveSpeed * dt, 0);
    SetPosition(newPosition);
}

void BossRibby::Shoot()
{
    std::cout << "주먹 발사" << std::endl;
    shootCount++;

}

void BossRibby::ShootEnd()
{
}

void BossRibby::Ball()
{
}

void BossRibby::ballEnd()
{
}

void BossRibby::Death()
{
    isAlive = false;
    SetState(State::None);
    animator.ClearEvent();
    animator.Play("animations/RibbyDeath.csv");
}

void BossRibby::OnDie()
{
    scene->RemoveGo(this);
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

    if (state != this->state)
    {
        preState = this->state;
        this->state = state;

        switch (state)
        {
        case BossRibby::State::Idle:
            if (preState == State::Pattern1)
            {
                animator.Play("animations/RibbyShootEnd.csv");
                animator.PlayQueue("animations/RibbyIdle.csv");
            }
            else if (preState == State::Pattern2)
            {
            }
            else
            {
                animator.PlayQueue("animations/RibbyIdle.csv");
            }
            preState = State::Idle;
            break;
        case BossRibby::State::Pattern1:
            if (shootCount < 7)
            {
                animator.Play("animations/RibbyShoot.csv");
                animator.PlayQueue("animations/RibbyShooting.csv");
            }
            else if (shootCount >= 7)
            {
                animator.Play("animations/RibbyShootEnd.csv");
            }
            animator.ClearEvent();
            animator.AddEvent("animations/RibbyShooting.csv", 4, std::bind(&BossRibby::Shoot, this));
            animator.AddEvent("animations/RibbyShooting.csv", 8, std::bind(&BossRibby::Shoot, this));
            preState = State::Pattern1;
            break;
        case BossRibby::State::Pattern2:

            preState = State::Pattern2;
            break;
        case BossRibby::State::Roll:
            animator.Play("animations/RibbyRoll.csv");
            animator.PlayQueue("animations/RibbyRolling.csv");
            if (preState == State::Pattern1) 
            {
                isMovingLeft = true;
            }
            else if (preState == State::Pattern2) 
            {
                isMovingRight = true;
            }
            preState = State::Roll;
            break;
        case BossRibby::State::None:
            break;
        default:
            break;
        }
    }
}

sf::FloatRect BossRibby::GetCustomBounds() const
{
    return customBounds;
}
