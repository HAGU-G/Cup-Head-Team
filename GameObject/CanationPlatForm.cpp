#include "pch.h"
#include "CanationPlatForm.h"
#include "SceneGame.h"
#include "Player.h"

CanationPlatForm::CanationPlatForm(const std::string& name)
    :SpriteGo(name)
{
}

CanationPlatForm* CanationPlatForm::Create(const sf::Vector2f& pos, Scene* scene)
{
	CanationPlatForm* cpf = new CanationPlatForm();
	cpf->scene = scene;
	cpf->SetPosition(pos);
	cpf->Init();
	cpf->Reset();
	dynamic_cast<SceneGame*>(scene)->Addtoehold(cpf);
	return cpf;
}

void CanationPlatForm::Update(float dt)
{
	SpriteGo::Update(dt);
	SetCustomBounds(0.65f, 0.6f, Origins::TC);
	
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	if (player != nullptr)
	{

		if (onPlatForm && newPos.y < Pos.y + 15.f)
		{
			std::cout << "true" << std::endl;
			newPos.x = position.x;
			newPos.y = position.y + speed * dt;
			SetPosition(newPos);
		}
		else if (!onPlatForm)
		{
			std::cout << "false" << std::endl;
			newPos.y = position.y - speed * dt;
			SetPosition(newPos);
			if (newPos.y <= Pos.y)
			{
				SetPosition(Pos);
			}
		}
	}
	customBounds.setPosition({ position.x, position.y - sprite.getGlobalBounds().height * 0.75f});


}

void CanationPlatForm::Init()
{
	SpriteGo::Init();
	scene = SCENE_MGR.GetCurrentScene();
	scene->AddGo(this);
	animator.SetTarget(&sprite);
	animator.Play("animations/carnationPlatForm.csv");
	scene->FindGo("Player");
	hasHitBox = true;
	newPos = sprite.getPosition();
	Pos = sprite.getPosition();
	speed = 300.f;
}

sf::RectangleShape CanationPlatForm::GetCustomBounds() const
{
    return customBounds;
}

void CanationPlatForm::Draw(sf::RenderTexture& window)
{
	SpriteGo::Draw(window);
}
