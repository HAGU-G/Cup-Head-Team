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
	text.setFillColor(colorUnSelect);
}

void ObjectButton::Release()
{
	if (nextButton->preButton == this)
	{
		nextButton->preButton = nullptr;
	}
	if (preButton->nextButton == this)
	{
		preButton->nextButton = nullptr;
	}
	TextGo::Release();
}

void ObjectButton::Select(bool playSound)
{
	if (playSound)
	{
		SOUND_MGR.PlaySfx("resource/Menu/Menu_Move.wav");
	}
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

ObjectButton* ObjectButton::ButtonMove(bool direction)
{
	if (direction && nextButton)
	{
		nextButton->Select();
		UnSelect();
		return nextButton;
	}
	else if (preButton)
	{
		preButton->Select();
		UnSelect();
		return preButton;
	}
	return this;
}

void ObjectButton::SetNextButton(ObjectButton* button, bool link)
{
	nextButton = button;
	if (link)
	{
		button->preButton = this;
	}
}
