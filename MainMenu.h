#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Animation.h"
using namespace std;
using namespace sf;
class MainMenu
{
private:
	Texture texture;
	Sprite sprite;
	Animation *animation;
	Text texts[3];

	void initTextures();
	void initSprites(RenderWindow& gameWindow);
	void initTexts(Font & gameFont,RenderWindow & gameWindow);
public:
	MainMenu(Font& gameFont, RenderWindow& gameWindow);
	virtual ~MainMenu();
	void display(RenderWindow & gameWindow, Time *elapsed);
};

