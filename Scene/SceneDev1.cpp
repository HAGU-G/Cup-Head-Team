#include "pch.h"
#include "SceneDev1.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "rapidcsv.h"
#include <filesystem> 
#include <ShObjIdl.h>
#include "rapidcsv.h"

namespace fs = std::filesystem;

SceneDev1::SceneDev1(SceneIds id)
    : Scene(id)
{
}

SceneDev1::~SceneDev1()
{
}

std::string ConvertLPCWSTRToString(LPCWSTR lpcwszStr)
{
    int strLength = WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1, nullptr, 0, nullptr, nullptr);
    if (strLength == 0)
    {
        return "";
    }
    std::string str(strLength, 0);

    if (WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1, &str[0], strLength, nullptr, nullptr) == 0)
    {
        return "";
    }

    return str;
}

std::vector<std::wstring> SceneDev1::SelectMultipleFiles()
{
    std::vector<std::wstring> files;
    //selectedFilePaths.clear();

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            DWORD dwOptions;
            pFileOpen->GetOptions(&dwOptions);
            pFileOpen->SetOptions(dwOptions | FOS_ALLOWMULTISELECT);

            hr = pFileOpen->Show(NULL);

            if (SUCCEEDED(hr))
            {
                IShellItemArray* pItems;
                hr = pFileOpen->GetResults(&pItems);
                if (SUCCEEDED(hr))
                {
                    DWORD dwNumItems;
                    pItems->GetCount(&dwNumItems);
                    for (DWORD i = 0; i < dwNumItems; i++)
                    {
                        IShellItem* pItem;
                        hr = pItems->GetItemAt(i, &pItem);
                        if (SUCCEEDED(hr))
                        {
                            PWSTR pszFilePath;
                            hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                            if (SUCCEEDED(hr))
                            {
                                files.push_back(pszFilePath);
                                CoTaskMemFree(pszFilePath);
                            }
                            pItem->Release();
                        }
                    }
                    pItems->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }

    return files;
}

void SceneDev1::LoadImagesAndDisplay()
{
    auto filePaths = SelectMultipleFiles();

    int maxHeight = 0;
    int totalWidth = 0;

    sprites.clear();
    textures.clear();
    std::cout << "파일 이름 :" << std::endl;
    std::cin >> renderTextureName;
    int num;
    std::cout << " -----------------------------------------" << std::endl;
    std::cout << " : 1. 좌측상단 2. 좌측 중앙 3. 좌측 하단 :" << std::endl;
    std::cout << " -----------------------------------------" << std::endl;
    std::cin >> num;
    if (num > 3 || num < 1)
    {
        std::cout << "스프라이트 시트 기준점이 틀립니다 다시 입력하세요." << std::endl;
        std::cin >> num;
    }
    std::cout << "스프라이트 시트 기준점이 설정되었습니다." << std::endl;

    for (const auto& filePath : filePaths)
    {
        sf::Texture* texture = new sf::Texture();
        if (texture->loadFromFile(ConvertLPCWSTRToString(filePath.c_str())))
        {
            textures.push_back(texture);

            sf::Sprite* sprite = new sf::Sprite;
            sprite->setTexture(*textures.back());

            const int spriteWidth = texture->getSize().x;
            const int spriteHeight = texture->getSize().y;

            if (spriteHeight > maxHeight)
            {
                maxHeight = spriteHeight;
            }

            spriteBound = sprite->getGlobalBounds();
            if (num == 1)
            {
                sprite->setOrigin(spriteBound.left, spriteBound.top);
            }
            else if (num == 2)
            {
                sprite->setOrigin(spriteBound.left, spriteBound.height / 2);
            }
            else if (num == 3)
            {
                sprite->setOrigin(spriteBound.left, spriteBound.height);
            }


            sprites.push_back(sprite);

            totalWidth += spriteWidth;
        }
        else
        {
            std::wcerr << L"Failed to load image: " << std::endl;
        }
    }
    if (!renderTexture.create(totalWidth, maxHeight))
    {
        std::cerr << "Failed to create render texture" << std::endl;
        return;
    }

    for (const auto& sprite : sprites)
    {
        if (num == 1)
        {
            sprite->setPosition({ spritePos.x,0.f });
        }
        else if (num == 2)
        {
            sprite->setPosition({ spritePos.x,(float)maxHeight / 2 });
        }
        else if (num == 3)
        {
            sprite->setPosition({ spritePos.x,(float)maxHeight });
        }
        spritePos.x += sprite->getGlobalBounds().width;

        renderTexture.draw(*sprite);

    }
    renderTexture.display();
}

void SceneDev1::SaveSpriteSheet()
{
    const sf::Texture& texture = renderTexture.getTexture();
    sf::Image image = texture.copyToImage();
    renderTextureName += ".png";
    image.saveToFile("graphics/" + renderTextureName);
    std::cout << "저장 완료" << std::endl;
}

void SceneDev1::Init()
{
}

void SceneDev1::Release()
{
    Scene::Release();
}

void SceneDev1::Enter()
{
    Scene::Enter();
}

void SceneDev1::Exit()
{
    Scene::Exit();
}

void SceneDev1::Update(float dt)
{
    if (InputMgr::GetKeyDown(sf::Keyboard::F1))
    {
        LoadImagesAndDisplay();
    }

    if (InputMgr::GetKeyDown(sf::Keyboard::Space))
    {
        SaveSpriteSheet();
    }
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);

    sf::Vector2f textureSize = (sf::Vector2f)renderTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = windowSize.x / textureSize.x;
    float scaleY = windowSize.y / textureSize.y;

    float scaleFactor = std::min(scaleX, scaleY);

    sf::View view(sf::FloatRect(0, 0, textureSize.x, textureSize.x));
    view.setCenter(textureSize.x / 2, textureSize.y / 2);
    view.setSize(windowSize.x / scaleFactor, windowSize.y / scaleFactor);

    window.setView(view);
    window.draw(sf::Sprite(renderTexture.getTexture()));
    window.setView(window.getDefaultView());
}
