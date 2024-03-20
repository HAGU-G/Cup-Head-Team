#pragma once

class Player;

class CollisionManager
{
public:
	enum AttackTypes
	{
		None = -1,
		Bullet,
		Parry,
	};

protected:
	std::list<GameObject*> BulletList;
	std::list<GameObject*> monsterList;
    //std::list<GameObject*> playerList;

	Player* player;
public:
    CollisionManager();
    ~CollisionManager();

	void Reset();

	bool BulletCollsion();
	bool ParryCollsion();
	bool PlayerCollsion();

    void RegisterMonsterCollider(GameObject* collider);
    void RegisterBulletCollider(GameObject* collider);
    void MonsterCollisions();
    void BulletCollisions();


};

