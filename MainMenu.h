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
	Texture background_texture;
	Sprite sprite;
	Sprite background;
	Animation *animation;
	Text texts[3];
	enum select { Play = 1, Exit = 0 };
	select selectedButton;

	void initTextures();
	void initSprites(RenderWindow& gameWindow);
	void initTexts(Font & gameFont,RenderWindow & gameWindow);
	void update();
public:
	MainMenu(Font& gameFont, RenderWindow& gameWindow);
	void display(RenderWindow & gameWindow, Time *elapsed);
	void selectUp();
	void selectDown();
	bool returnPlaySelected();
	bool returnExitSelected();
};

