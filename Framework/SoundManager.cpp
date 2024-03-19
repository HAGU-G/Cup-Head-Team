#include "pch.h"
#include "SoundManager.h"
#include <ResourceManager.h>

//////////////////////////////////////////////////////////////////////////////////////////////
//    
//     Sound
// 
//////////////////////////////////////////////////////////////////////////////////////////////
std::pair<std::pair<std::string, sf::Sound>, std::pair<std::string, sf::Sound>> SoundManager::bgm[2];

std::list<std::shared_ptr<sf::Sound>> SoundManager::usingSfx;
std::list<std::shared_ptr<sf::Sound>> SoundManager::waitingSfx;
float SoundManager::bgmVolume = 100.f;
float SoundManager::bgm1Fade = 100.f;
float SoundManager::bgm2Fade = 100.f;
float SoundManager::bgm1Volume = 100.f;
float SoundManager::bgm2Volume = 100.f;
int SoundManager::mainChannel = 0;
bool SoundManager::isCrossFading = false;
float SoundManager::fadeDuration = 5.f;

void SoundManager::SoundInit(int sfxCount)
{
	for (int i = 0; i < sfxCount; i++)
	{
		waitingSfx.push_back(std::make_shared<sf::Sound>());
	}
}

void SoundManager::SoundUpdate(float timeDelta, float timeScale)
{
	CrossFade(timeDelta);

	auto it = usingSfx.begin();
	while (it != usingSfx.end())
	{
		if ((*it)->getStatus() == sf::Sound::Stopped)
		{
			waitingSfx.push_back((*it));
			it = usingSfx.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void SoundManager::SoundRelease()
{
	bgm[0].first.second.stop();
	bgm[0].second.second.stop();
	bgm[1].first.second.stop();
	bgm[1].second.second.stop();

	for (auto& ptr : usingSfx)
	{
		ptr->stop();
	}
	usingSfx.clear();
	waitingSfx.clear();

}

void SoundManager::PlayBGMCh1(const std::string& path, bool crossFade, bool loop)
{
	if (crossFade)
	{
		mainChannel = 1 - mainChannel;
		isCrossFading = true;
		bgm1Fade = 0.f;
		BGMVolumeRatio();
	}

	bgm[mainChannel].first.second.setLoop(loop);
	if (bgm[mainChannel].first.first != path)
	{
		bgm[mainChannel].first.second.stop();
		bgm[mainChannel].first.second.setBuffer(SFGM_SOUNDBUFFER.Get(path));
		bgm[mainChannel].first.first = path;
		bgm[mainChannel].first.second.play();
	}
}

void SoundManager::PlayBGMCh2(const std::string& path, bool crossFade, bool loop)
{
	if (crossFade)
	{
		mainChannel = 1 - mainChannel;
		isCrossFading = true;
		bgm2Fade = 0.f;
		BGMVolumeRatio();
	}

	bgm[mainChannel].second.second.setLoop(loop);
	if (bgm[mainChannel].second.first != path)
	{
		bgm[mainChannel].second.second.stop();
		bgm[mainChannel].second.second.setBuffer(SFGM_SOUNDBUFFER.Get(path));
		bgm[mainChannel].second.first = path;
		bgm[mainChannel].second.second.play();
	}

}


void SoundManager::BGMSyncPlay(const std::string& path1, const std::string& path2, bool crossFade, bool loop)
{
	if (crossFade)
	{
		mainChannel = 1 - mainChannel;
		isCrossFading = true;
		bgm1Fade = 0.f;
		bgm2Fade = 0.f;
		BGMVolumeRatio();
	}

	if (bgm->first.first != path1)
	{
		bgm[mainChannel].first.second.stop();
		bgm[mainChannel].first.second.setBuffer(SFGM_SOUNDBUFFER.Get(path1));
		bgm[mainChannel].first.first = path1;
	}
	if (bgm->second.first != path2)
	{
		bgm[mainChannel].second.second.stop();
		bgm[mainChannel].second.second.setBuffer(SFGM_SOUNDBUFFER.Get(path2));
		bgm[mainChannel].second.first = path2;
	}
	bgm[mainChannel].first.second.setLoop(loop);
	bgm[mainChannel].second.second.setLoop(loop);

	bgm[mainChannel].first.second.play();
	bgm[mainChannel].second.second.play();
}

std::shared_ptr<sf::Sound> SoundManager::PlaySfx(const std::string& path, bool listener, bool play)
{
	std::shared_ptr<sf::Sound> sfx;
	if (waitingSfx.empty())
	{
		sfx = usingSfx.front();
		usingSfx.pop_front();
		sfx->stop();
	}
	else
	{
		sfx = waitingSfx.front();
		waitingSfx.pop_front();
	}

	sfx->setBuffer(SFGM_SOUNDBUFFER.Get(path));
	sfx->setPosition(0.f, 0.f, 0.f);
	sfx->setMinDistance(1);
	sfx->setAttenuation(1);
	sfx->setRelativeToListener(listener);
	usingSfx.push_back(sfx);
	if (play)
		sfx->play();
	return sfx;
}

float SoundManager::PlaySfx(const std::string& path, sf::Vector3f pos, float minD, float atte)
{
	std::shared_ptr<sf::Sound> sfx = PlaySfx(path, false, false);
	sfx->setPosition(pos);
	sfx->setMinDistance(minD);
	sfx->setAttenuation(atte);
	sfx->play();
	return sfx->getBuffer()->getDuration().asSeconds();
}

void SoundManager::SetFadeDuration(float duration)
{
	fadeDuration = duration;
}

void SoundManager::SetBGMCh1Volume(float volume)
{
	bgm1Volume = Utils::Clamp(volume, 0.f, 100.f);
	BGMVolumeRatio();
}

void SoundManager::SetBGMCh2Volume(float volume)
{
	bgm2Volume = Utils::Clamp(volume, 0.f, 100.f);
	BGMVolumeRatio();
}

void SoundManager::BGMVolumeRatio()
{
	bgm[mainChannel].first.second.setVolume(bgm1Volume * bgmVolume / 100.f * bgm1Fade / 100.f);
	bgm[mainChannel].second.second.setVolume(bgm2Volume * bgmVolume / 100.f * bgm2Fade / 100.f);
}

void SoundManager::CrossFade(float timeDelta)
{
	if (bgm[1 - mainChannel].first.second.getVolume() == 0.f && bgm[1 - mainChannel].second.second.getVolume() == 0.f
		&& bgm1Fade == 100.f && bgm2Fade == 100.f)
	{
		bgm[1 - mainChannel].first.second.stop();
		bgm[1 - mainChannel].second.second.stop();
		isCrossFading = false;
	}
	else
	{
		bgm1Fade = Utils::Clamp(bgm1Fade + (100.f / fadeDuration) * timeDelta, 0.f, 100.f);
		bgm2Fade = Utils::Clamp(bgm2Fade + (100.f / fadeDuration) * timeDelta, 0.f, 100.f);
		float volumeMain1 = Utils::Clamp(bgm[1 - mainChannel].first.second.getVolume() - (100.f / fadeDuration) * timeDelta, 0.f, 100.f);
		float volumeMain2 = Utils::Clamp(bgm[1 - mainChannel].second.second.getVolume() - (100.f / fadeDuration) * timeDelta, 0.f, 100.f);
		bgm[1 - mainChannel].first.second.setVolume(volumeMain1);
		bgm[1 - mainChannel].second.second.setVolume(volumeMain2);
		BGMVolumeRatio();
	}
}

void SoundManager::StopBGM(unsigned int channel)
{
	if (channel <= 1)
	{
		bgm[0].first.second.stop();
		bgm[1].first.second.stop();
	}
	else
	{
		bgm[0].second.second.stop();
		bgm[1].second.second.stop();
	}
}

void SoundManager::StopBGM()
{
	bgm[0].first.second.stop();
	bgm[0].second.second.stop();
	bgm[1].first.second.stop();
	bgm[1].second.second.stop();
}

void SoundManager::SetVolume(float volume)
{
	sf::Listener::setGlobalVolume(volume);
}

void SoundManager::SetBGMVolume(float volume)
{
	bgmVolume = volume;
	BGMVolumeRatio();
}
