#pragma once
#include "Animator.h"

class SpriteGo;
class TextGo;
class AnimationTool;

class SceneDev1 : public Scene
{
protected:
	AnimationTool* aniTool;

	std::vector<sf::Texture*> textures;
	std::vector<sf::Sprite*> sprites;

	TextGo* loadFile;
	TextGo* saveFile;
	TextGo* resetFile;

	sf::FloatRect spriteBound;
	sf::RenderTexture renderTexture;
	sf::RenderWindow window;

	sf::RectangleShape loadShape;
	sf::RectangleShape saveShape;
	sf::RectangleShape resetShape;

	Animator animator;

	std::string renderTextureName;
	std::string filePathId;

	int fps = 0;
	int loopType = 0;
	int setOrigin = 0;

	int sheetWidth = 0;
	int sheetHeight = 0;
	sf::Vector2f spritePos = { 0.f,0.f };

	bool AddHeight = false;
	bool fileLoad = false;
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
	void Draw(sf::RenderTexture& window);

	std::vector<std::wstring> selectedFilePaths;
};

