#include "pch.h"
#include "ObjectButton.h"

ObjectButton::ObjectButton(const std::string& name)
	:TextGo(name)
{
}

void ObjectButton::Init()
{
	TextGo::Init();
	text.setFont(RES_MGR_FONT.Get("resource/Font/YoonBackjaeM Bold.ttf"));
	text.setCharacterSize(50);
	text.setFillColor(colorUnSelect);
}

void ObjectButton::Select()
{
	SOUND_MGR.PlaySfx("resource/Menu/Menu_Move.wav");
	isSelected = true;
	text.setFillColor(colorSelect);
}

void ObjectButton::Press()
{
	SOUND_MGR.PlaySfx("resource/Menu/Menu_Category_Select.wav");
	if (func)
	{
		func();
	}
}

void ObjectButton::UnSelect()
{
	isSelected = false;
	text.setFillColor(colorUnSelect);
}

void ObjectButton::SetFunction(std::function<ObjectButton*()> funtion)
{
	func = funtion;
}
