#pragma once


class SceneDev1 : public Scene
{
protected:
	std::vector<sf::Texture*> textures;
	std::vector<sf::Sprite*> sprites;

	sf::FloatRect spriteBound;
	sf::RenderTexture renderTexture;

	Animator animator;

	std::string renderTextureName;
	std::string filePathId;

	int fps = 0;
	int loopType = 0;
	int setOrigin = 0;

	int sheetWidth = 0;
	int sheetHeight = 0;
	sf::Vector2f spritePos = { 0.f,0.f };

public:
	SceneDev1(SceneIds id);
	virtual ~SceneDev1();

	void LoadImagesAndDisplay();
	std::vector<std::wstring> SelectMultipleFiles();

	void SaveSpriteSheet();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;
	void Reset();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	std::vector<std::wstring> selectedFilePaths;
};

