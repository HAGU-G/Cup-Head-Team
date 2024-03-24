#include "pch.h"
#include "BossRibby.h"
#include "SceneGame.h"
#include "Bullet/BulletRibbyShoot.h"
#include "Bullet/BulletRibbyBall.h"

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
    RES_MGR_TEXTURE.Load("resource/RibbyIntro2.png");
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
        if (PatternTimer(dt) && hp > maxHp * 0.60)
        {
            SetState(State::Pattern1);
        }
        if (PatternTimer(dt) && hp <= maxHp * 0.40)
        {
            SetState(State::Pattern2);
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
        if (hp <= maxHp * 0.30 && state != State::Roll)
        {
            SetState(State::Roll);
        }
        if (state == State::Pattern2 && ballCount > 2)
        {
            ballCount = 0;
            SetState(State::Idle);
        }
        break;
    case BossRibby::State::Roll:
        if (isRolling) 
        {
            if (isMovingRight) 
            {
                MoveToRight(dt);
            }
            if (isMovingLeft) 
            {
                MoveToLeft(dt);
            }
        }
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
    if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
    {
        SetState(State::Pattern1);
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
    isRolling = false;
    SetState(State::Roll);
    animator.Play("animations/RibbyRoll.csv"); // Roll 애니메이션 재생
    animator.AddEvent("animations/RibbyRoll.csv", animator.GetCurrentClip()->GetTotalFrame(), [this]() 
        {
        // Roll 애니메이션이 끝나면 Rolling 애니메이션 시작
        animator.Play("animations/RibbyRolling.csv");
        isRolling = true;
        });
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
    float yOffset;
    if (shootCount == 0 || shootCount == 4) 
    {
        yOffset = sprite.getGlobalBounds().height * 1.f / 8.f;
    }
    else if (shootCount == 1 || shootCount == 3 || shootCount == 5) 
    {
        yOffset = sprite.getGlobalBounds().height * 4.f / 8.f;
    }
    else 
    {
        yOffset = sprite.getGlobalBounds().height * 7.f / 8.f;
    }

    sf::Vector2f bulletPosition = sf::Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + yOffset);

    if (shootCount < 7)
    {
        BulletRibbyShoot::Create(bulletPosition, { -1.f, 0.f }, scene);
    }
    shootCount++;
    if (shootCount >= 7) 
    {
        shootCount = 0;
        SetState(State::Idle);
    }
}

void BossRibby::ShootEnd()
{
}

void BossRibby::Ball()
{
    sf::Vector2f ballDirection;
    if (ballCount == 0 || ballCount == 2)
    {
        ballDirection = {-1,2};
    }
    else
    {
        ballDirection = { -1,-2 };
    }
    BulletRibbyBall::Create(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width * 0.3f, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 0.4f), ballDirection, scene);
    std::cout << ballCount << std::endl;
    ballCount++;
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
                animator.PlayQueue("animations/RibbyIdle.csv");
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
            preState = State::Pattern1;
            break;
        case BossRibby::State::Pattern2:
            if (preState == State::Roll)
            {
                Intro2();
            }

            if (ballCount < 3)
            {
                animator.PlayQueue("animations/RibbyBall.csv");
            }
            animator.ClearEvent();
            animator.AddEvent("animations/RibbyBall.csv", 23, std::bind(&BossRibby::Ball, this));
            preState = State::Pattern2;
            break;
        case BossRibby::State::Roll:  //수정이 필요함 (화면 경계 검사 :  밖에 나가면 다음 intro2실행)
            Roll();
            if (preState == State::Pattern1) 
            {
                isMovingLeft = true;
                isMovingRight = false;
            }
            else if (preState == State::Pattern2) 
            {
                isMovingRight = true;
                isMovingLeft = false;
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
