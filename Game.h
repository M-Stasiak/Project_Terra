#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "DeathScreen.h"
#include "Background.h"
#include "Entity.h"
#include "Player.h"
#include "Zombie.h"
#include "Skeleton.h"
#include "Mushroom.h"
#include "Slime.h"
#include "GameWorld.h"
#include "Blocks.h"
#include "Inventory.h"
#include "Item.h"
#include "Items.h"

using namespace sf;
using namespace std;
class Game
{
private:
	float deathScreenTime = 10, appleUseTime = 1;
	int renderWidth = 32, renderHeight = 19;
	//int renderWidth = 3, renderHeight = 3;
	int collisionsCheckWidth = 3, collisionsCheckHeight = 3;
	enum class gameMode{mainMenu,pauseMenu,playing,inventory,dead};
	gameMode currentGameMode;
	RenderWindow gameWindow;
	Event gameEvent;
	Font gameFont;
	MainMenu *mainMenu;
	PauseMenu* pauseMenu;
	DeathScreen* deathScreen;
	Inventory* inventory;
	Player player;
	Music gameMusic;
	SoundBuffer bufferItemPickUp, bufferInventoryOpen, bufferInventoryClose;
	Sound soundItemPickUp, soundInventoryOpen, soundInventoryClose;
	
	void initFont();
	void initWindow();
	void initBackground();
	void setGameView();
	void updateItemsOnTheGround(GameWorld& world, Time &elapsed);
	void destroyBlock(GameWorld& world, map <IDs, Block*>& Blocks, map <IDs, Texture*>& BlocksTextures, map <IDs, Texture*>& ItemsTextures, map <IDs, Item*>& Items);
	void updateEntities(vector<Entity*>& entities, Time& elapsed, GameWorld& world);
	void updateBlocks(GameWorld& world, map <IDs, Block*>& Blocks);
	void dropMouseItemsRight(GameWorld& world, map <IDs, Block*>& Blocks, map <IDs, Texture*>& BlocksTextures, map <IDs, Texture*>& ItemsTextures, map <IDs, Item*>& Items);
	void dropMouseItemsLeft(GameWorld& world, map <IDs, Block*>& Blocks, map <IDs, Texture*>& BlocksTextures, map <IDs, Texture*>& ItemsTextures, map <IDs, Item*>& Items);

public:
	Game();
	void dispGame();

};

