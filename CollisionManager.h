#pragma once
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
	std::list<GameObject> bulletList;
	std::list<GameObject> parryList;
	
public:
	
	bool BulletCollsion();
	bool ParryCollsion();

	void Bullet();
	void Parry();


};

