#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
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
	Music music;
	Animation *animation;
	Text texts[3];
	enum select { Play = 1, Exit = 0 };
	select selectedButton;
	enum mouse { play = 1, exit = 0,none = 2 };
	mouse mouseOnButton;

	void initTextures();
	void initSprites(RenderWindow& gameWindow);
	void initTexts(Font & gameFont,RenderWindow & gameWindow);
	void update(RenderWindow& gameWindow);
public:
	MainMenu(Font& gameFont, RenderWindow& gameWindow);
	void display(RenderWindow & gameWindow, Time *elapsed);
	void selectUp();
	void selectDown();
	void musicOn() { if (music.getStatus() != Music::Playing) music.play(); };
	void musicOff() { if (music.getStatus() == Music::Playing) music.stop(); };
	int returnSelectedButton();
	int returnMouseOnButton();
	
};

