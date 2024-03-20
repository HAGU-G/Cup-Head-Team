#include "pch.h"
#include "CollisionManager.h"
#include "Player.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Reset()
{
}

bool CollisionManager::BulletCollsion()
{

    return false;
}

bool CollisionManager::ParryCollsion()
{

    return false;
}

bool CollisionManager::PlayerCollsion()
{

    return false;
}

void CollisionManager::RegisterMonsterCollider(GameObject* collider)
{
    monsterList.push_back(collider);
}

void CollisionManager::RegisterBulletCollider(GameObject* collider)
{
    BulletList.push_back(collider);
}

void CollisionManager::MonsterCollisions()
{
    for (GameObject* collider : monsterList)
    {
        //collider->OnBulletHit();
    }
}

void CollisionManager::BulletCollisions()
{
    for (GameObject* collider : BulletList)
    {
        //collider->OnParryHit();
    }
}
