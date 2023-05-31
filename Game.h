#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Background.h"
#include "Entity.h"
#include "Player.h"
#include "GameWorld.h"
#include "Blocks.h"
#include "Inventory.h"
#include "Item.h"
#include "Block_Item.h"

using namespace sf;
using namespace std;
class Game
{
private:
	int renderWidth = 32, renderHeight = 19;
	//int renderWidth = 3, renderHeight = 3;
	int collisionsCheckWidth = 3, collisionsCheckHeight = 3;
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
	void initBackground();
	void setGameView();
	

public:
	Game();
	void dispGame();

};

