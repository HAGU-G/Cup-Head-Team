#pragma once

class SpriteGo;

class SceneDev1 : public Scene
{
protected:
	std::vector<sf::Texture*> textures;
	std::vector<sf::Sprite*> sprites;

	sf::FloatRect spriteBound;
	sf::RenderTexture renderTexture;
	sf::Vector2f spritePos = { 0.f,0.f };

	std::string renderTextureName;

	sf::Texture testtex;
	sf::Sprite testSprite;

	int sheetWidth = 0;
	int sheetHeight = 0;
	sf::Vector2f scale = { 1.f,1.f };


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

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	std::vector<std::wstring> selectedFilePaths;
};

