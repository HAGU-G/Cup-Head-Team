#pragma once
class SoundManager
{
	//////////////////////////////////////////////////////////////////////////////////////////////
//    
//     Sound
// 
//////////////////////////////////////////////////////////////////////////////////////////////

private:
	static std::pair<std::pair<std::string, sf::Sound>, std::pair<std::string, sf::Sound>> bgm[2]; // 0=main
	static int mainChannel;
	static bool isCrossFading;
	static float fadeDuration;


	static std::list<std::shared_ptr<sf::Sound>> usingSfx;
	static std::list<std::shared_ptr<sf::Sound>> waitingSfx;

	static float bgmVolume;
	static float bgm1Volume;
	static float bgm2Volume;
	static float bgm1Fade;
	static float bgm2Fade;

	static void BGMVolumeRatio();
	static void CrossFade(float timeDelta);

public:
	static void SoundInit(int sfxCount = 64);
	static void SoundUpdate(float timeDelta, float timeScale);
	static void SoundRelease();

	static void PlayBGMCh1(const std::string& path, bool crossFade = true, bool loop = true);
	static void PlayBGMCh2(const std::string& path, bool crossFade = true, bool loop = true);
	static void StopBGM();
	static void StopBGM(unsigned int channel);

	static void SetFadeDuration(float duration);
	static void SetBGMCh1Volume(float volume);
	static void SetBGMCh2Volume(float volume);
	static void SetVolume(float volume);
	static void SetBGMVolume(float volume);

	static void BGMSyncPlay(const std::string& path1, const std::string& path2, bool crossFade = true, bool loop = true);


	static std::shared_ptr<sf::Sound> PlaySfx(const std::string& path, bool listener = true, bool play = true);
	static float PlaySfx(const std::string& path, sf::Vector3f pos, float minD, float Atte);
};

