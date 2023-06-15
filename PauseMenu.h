#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animation.h"
using namespace std;
using namespace sf;
class PauseMenu
{
private:
	Texture background;
	Sprite backgroundSprite;
	Text texts[3];
	enum select { Continue = 1, Exit = 0 };
	select selectedButton;
	enum mouse { continue1 = 1, exit = 0, none = 2 };
	mouse mouseOnButton;
	SoundBuffer bufferTick;
	Sound soundTick;

	void initTextures();
	void initSprites(RenderWindow& gameWindow);
	void initTexts(Font& gameFont, RenderWindow& gameWindow);
	void update(RenderWindow& gameWindow);
public:
	PauseMenu(Font& gameFont, RenderWindow& gameWindow);
	void display(RenderWindow& gameWindow, Time* elapsed);
	void selectUp();
	void selectDown();
	int returnSelectedButton();
	int returnMouseOnButton();
};


