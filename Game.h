#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include "MainMenu.h"

using namespace sf;
using namespace std;
class Game
{
private:
	enum class gameMode{mainMenu,pauseMenu,playing,inventory};
	gameMode currentGameMode;
	RenderWindow gameWindow;
	Event gameEvent;
	Font gameFont;
	MainMenu *mainMenu;
	
	void initFont();
	void initWindow();
	

public:
	Game();
	void dispGame();

};

