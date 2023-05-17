#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
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

	void initTextures();
	void initSprites();
	void initTexts(Font& gameFont, RenderWindow& gameWindow);
	void update(RenderWindow& gameWindow);
public:
	PauseMenu(Font& gameFont, RenderWindow& gameWindow);
	void display(RenderWindow& gameWindow, Time* elapsed);
	void selectUp();
	void selectDown();
	bool returnContinueSelected();
	bool returnExitSelected();
};


