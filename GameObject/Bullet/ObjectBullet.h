#pragma once
#include "SpriteGo.h"


class ObjectBullet : public SpriteGo
{
protected:
	enum class Type
	{
		Straight,	//������
		Homing,		//������
	};
	enum class Owner	//���� ������� ����.
	{
		Player,			//���� : �÷��̾�
		Enemy,			//���� : ��
	};

	Type type = Type::Straight;
	Owner owner = Owner::Player;

	sf::Vector2f prePosition;
	sf::Vector2f direction;			//���ư� ����
	sf::Vector2f targetPosition;	//��ǥ ��ǥ (Homing)
	float speed = 0.f;
	float rotateSpeed = 0.f;
	float range = 0.f;
	float moveDistance = 0.f;
	bool doHoming = true;

	sf::RectangleShape bound;			//�浹 �˻�� bound���� ��. 2024-03-20 ����

	virtual void Flip();				//�̵� ���⿡ �°� ��������Ʈ ������ �����մϴ�.
	virtual void Homing(float dt);		//���� �����ϴ� �Լ�

public:
	ObjectBullet(const std::string& name = "Bullet");
	~ObjectBullet() override;
	ObjectBullet(const ObjectBullet&) = delete;
	ObjectBullet(ObjectBullet&&) = delete;
	ObjectBullet& operator=(const ObjectBullet&) = delete;
	ObjectBullet& operator=(ObjectBullet&&) = delete;

	void CreateInit(const sf::Vector2f& pos, const sf::Vector2f& direction, Scene* scene); //��ġ, ���ư� ����, ���� �־��ָ� Init���� AddGo���� ��� �մϴ�.

	void Init() override;
	void Release() override;

	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void Draw(sf::RenderTexture& window) override;

	inline void SetSpeed(float speed) { this->speed = speed; }							//�̵��ӵ� ����
	inline void SetRotateSpeed(float rotateSpeed) { this->rotateSpeed = rotateSpeed; }	//ȸ���ӵ� ���� : �ʴ� rotateSpeed ��ŭ ȸ��, degree
	inline void SetRange(float range) { this->range = range; }							//�����Ÿ� ���� (�̵��Ÿ��� ���)
	void SetDirection(Direction direction);												//���� ����
	void SetDirection(const sf::Vector2f& direction, bool isConversed = false);			//���� ���� : direction�� ���ڷ� �Ѱ��ָ� �˴ϴ�.
	void SetPosition(const sf::Vector2f& position) override;							//��ġ ����
	void SetTargetPosition(const sf::Vector2f position);								//��ǥ ��ǥ ����

	virtual void OnCreate();	//CreateInit�� �ϸ� �ڵ����� ȣ��Ǵ� �Լ� : ������ ����ֽ��ϴ�.
	virtual void OnDie();		//������ Remove �ϰ���� �� ȣ���Ͻø� �˴ϴ�.




};

