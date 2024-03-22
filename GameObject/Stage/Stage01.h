#pragma once
#include "GameObject.h"

class BossPotato;
class BossOnion;
class BossCarrot;

class Stage01 : public GameObject
{
protected:
	BossPotato* potato = nullptr;
	BossOnion* onion = nullptr;
	BossCarrot* carrot = nullptr;

	int phase = 0;
	int totalHp = 0;


public:
	Stage01(const std::string& name = "Stage01");
	~Stage01() override = default;
	Stage01(const Stage01&) = delete;
	Stage01(Stage01&&) = delete;
	Stage01& operator=(const Stage01&) = delete;
	Stage01& operator=(Stage01&&) = delete;

	void Init() override;
	void Update(float dt) override;
	void Reset() override;
};

