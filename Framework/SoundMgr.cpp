#include "pch.h"
#include "SoundMgr.h"

SoundMgr::SoundMgr()
{
}

SoundMgr::~SoundMgr()
{
	Release();
}

void SoundMgr::SetSfxVolume(float v)
{
	sfxVolume = v;
	for (auto ptr : playing)
	{
		ptr->setVolume(sfxVolume);
	}
	for (auto ptr : waiting)
	{
		ptr->setVolume(sfxVolume);
	}
}

void SoundMgr::SetBgmVolume(float v)
{

	if (isFading)
	{
		bgm[frontBgmIndex].setVolume(bgm[frontBgmIndex].getVolume() * v / bgmVolume);
		bgmVolume = v;
	}
	else
	{
		bgmVolume = v;
		bgm[frontBgmIndex].setVolume(bgmVolume);
	}
}

void SoundMgr::Init(int totalChannels)
{
	Release();
	for (int i = 0; i < totalChannels; ++i)
	{
		waiting.push_back(new sf::Sound());
	}
}

void SoundMgr::Release()
{
	//StopAll();
	StopBgm();
	for (auto sound : waiting)
	{
		sound->stop();
		delete sound;
	}
	waiting.clear();
	for (auto sound : playing)
	{
		sound->stop();
		delete sound;
	}
	playing.clear();
}

void SoundMgr::Update(float dt)
{
	for (auto it = playing.begin(); it != playing.end(); )
	{
		sf::Sound* sound = *it;
		if (sound->getStatus() == sf::SoundSource::Stopped)
		{
			waiting.push_back(sound);
			it = playing.erase(it);
		}
		else
		{
			it++;
		}
	}

	// 크로스 페이드
	if (isFading)
	{
		bool isEndBack = false;
		bool isEndFront = false;

		int backBgmIndex = (frontBgmIndex == 1) ? 0 : 1;

		float backVolume = bgm[backBgmIndex].getVolume();
		backVolume = Utils::Lerp(backVolume, 0.f, dt * fadeSpeed);
		bgm[backBgmIndex].setVolume(backVolume);
		if (std::abs(backVolume) < fadeLimit)
		{
			bgm[backBgmIndex].setVolume(0.f);
			bgm[backBgmIndex].stop();
			isEndBack = true;
		}

		float frontVolume = bgm[frontBgmIndex].getVolume();
		frontVolume = Utils::Lerp(frontVolume, bgmVolume, dt * fadeSpeed);
		bgm[frontBgmIndex].setVolume(frontVolume);
		if (std::abs(backVolume - frontVolume) < fadeLimit)
		{
			bgm[frontBgmIndex].setVolume(bgmVolume);
			isEndFront = true;
		}

		if (isEndBack && isEndFront)
		{
			isFading = false;
		}
	}
}

void SoundMgr::PlayBgm(std::string id, bool crossFade, bool loop)
{
	if (crossFade)
	{
		frontBgmIndex = (frontBgmIndex + 1) % 2;
		isFading = true;
		bgm[frontBgmIndex].setVolume(0.f);
	}
	else
	{
		StopBgm();
		bgm[frontBgmIndex].setVolume(bgmVolume);
	}

	bgm[frontBgmIndex].setBuffer(RES_MGR_SOUND_BUFFER.Get(id));
	bgm[frontBgmIndex].setLoop(loop);
	bgm[frontBgmIndex].play();
}

void SoundMgr::StopBgm()
{
	isFading = false;
	//for (auto sound : bgm)
	//{
	//	sound.stop();
	//}
	for (int i = 0; i < 2; ++i) {
		bgm[i].stop();
	}
}

void SoundMgr::PlaySfx(std::string id, bool loop)
{
	PlaySfx(RES_MGR_SOUND_BUFFER.Get(id), loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;
	if (waiting.empty())
	{
		sound = playing.front();
		playing.pop_front();
		sound->stop();
	}
	else
	{
		sound = waiting.front();
		waiting.pop_front();
	}

	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->setVolume(sfxVolume);
	sound->play();
	playing.push_back(sound);
}

void SoundMgr::StopAll()
{
	for (auto sound : playing)
	{
		sound->stop();
		waiting.push_back(sound);
	}
	playing.clear();
}

void SoundMgr::PlayAllSfx()
{
	for (auto ptr : playing)
	{
		ptr->play();
	}
}

void SoundMgr::PauseAllSfx()
{
	for(auto ptr : playing)
	{
		ptr->pause();
	}
}
