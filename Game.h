#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Entity.h"
#include "Player.h"
#include "GameWorld.h"
#include "Block.h"

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
	PauseMenu* pauseMenu;
	
	void initFont();
	void initWindow();
	

public:
	Game();
	void dispGame();

};

