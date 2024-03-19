#pragma once

enum class AnimationLoopType
{
	Single,        // 1 2 3 
	Loop,          // 1 2 3 1 2 3
	Pingpong       // 1 2 3 2 1
};

struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;

	AnimationFrame(const std::string& id, const sf::IntRect& coord)
		: textureId(id), texCoord(coord)
	{

	}

	const sf::Texture& GetTexture() const
	{
		return RES_MGR_TEXTURE.Get(textureId);
	}
};

struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;
	AnimationLoopType looptype = AnimationLoopType::Single;
	int fps = 30;

	int GetTotalFrame() const
	{
		return frames.size();
	}

	bool loadFromFile(const std::string& filePath);
};

struct AnimationEvent
{
	std::string clipId;
	int frame;
	std::function<void()> action;             //반환형 void 매개변수 없음
};

class Animator
{
protected:
	//std::unordered_map<std::string, AnimationClip> clips;   //클립을 담아서 출력
	std::queue<std::string> queue;
	std::list<AnimationEvent> eventList;

	float speed = 1.f;

	bool isPlaying = false;
	AnimationClip* currentClip = nullptr;   //현재 플레이중인 애니매이션
	int totalFrame = 0;
	int currentFrame = -1;
	int addFrame = 1;
	float clipDuration = 0.f;

	float accumTime = 0.f;

	sf::Sprite* target;

public:
	Animator();
	~Animator();

	//void AddClip(const AnimationClip& clip);

	void AddEvent(const std::string& clipId, int frame, std::function<void()> action);
	void ClearEvent();

	bool IsPlaying() const { return isPlaying; }
	const std::string& GetCurrentCilpId()
	{
		return currentClip->id;
	}
	sf::Sprite* GetTarget() const { return target; }
	void SetTarget(sf::Sprite* t) { target = t; }

	float GetSpeed() const { return speed; }
	void SetSpeed(float s) { speed = s; }

	void Update(float dt);    //현재 재생되고 있는 시간을 누적하면서 프래임 변경

	void Play(const std::string& clipId, bool clearQueue = true);
	void PlayQueue(const std::string& clipId);
	void Stop();
	void SetFrame(const AnimationFrame& frame);
};

