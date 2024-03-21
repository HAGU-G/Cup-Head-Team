#pragma once
#include "SpriteGo.h"


class ObjectBullet : public SpriteGo
{
protected:
	enum class Type
	{
		Straight,	//직선형
		Homing,		//추적형
	};
	enum class Owner	//아직 사용하지 않음.
	{
		Player,			//주인 : 플레이어
		Enemy,			//주인 : 적
	};

	Type type = Type::Straight;
	Owner owner = Owner::Player;

	sf::Vector2f prePosition;
	sf::Vector2f direction;			//날아갈 방향
	sf::Vector2f targetPosition;	//목표 좌표 (Homing)
	float speed = 0.f;
	float rotateSpeed = 0.f;
	float range = 0.f;
	float moveDistance = 0.f;
	bool doHoming = true;

	sf::RectangleShape bound;			//충돌 검사용 bound였던 것. 2024-03-20 기준

	virtual void Flip();				//이동 방향에 맞게 스프라이트 방향을 설정합니다.
	virtual void Homing(float dt);		//적을 추적하는 함수

public:
	ObjectBullet(const std::string& name = "Bullet");
	~ObjectBullet() override;
	ObjectBullet(const ObjectBullet&) = delete;
	ObjectBullet(ObjectBullet&&) = delete;
	ObjectBullet& operator=(const ObjectBullet&) = delete;
	ObjectBullet& operator=(ObjectBullet&&) = delete;

	void CreateInit(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene); //위치, 날아갈 방향, 씬을 넣어주면 Init부터 AddGo까지 모두 합니다.

	void Init() override;
	void Release() override;

	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void Draw(sf::RenderTexture& window) override;

	inline void SetSpeed(float speed) { this->speed = speed; }							//이동속도 설정
	inline void SetRotateSpeed(float rotateSpeed) { this->rotateSpeed = rotateSpeed; }	//회전속도 설정 : 초당 rotateSpeed 만큼 회전, degree
	inline void SetRange(float range) { this->range = range; }							//사정거리 설정 (이동거리로 계산)
	void SetDirection(Direction direction);												//방향 설정
	void SetDirection(const sf::Vector2f& direction, bool isConversed = false);			//방향 설정 : direction만 인자로 넘겨주면 됩니다.
	void SetPosition(const sf::Vector2f& position) override;							//위치 설정
	void SetTargetPosition(const sf::Vector2f position);								//목표 좌표 설정

	virtual void OnCreate();	//CreateInit를 하면 자동으로 호출되는 함수 : 내용은 비어있습니다.
	virtual void OnDie();		//씬에서 Remove 하고싶을 때 호출하시면 됩니다.




};

