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
#include "Inventory.h"

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
	Inventory* inventory;
	Player player;
	
	void initFont();
	void initWindow();
	void setGameView();
	

public:
	Game();
	void dispGame();

};

