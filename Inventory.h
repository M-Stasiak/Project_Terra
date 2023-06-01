#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Item.h"
using namespace std;
using namespace sf;
class Inventory
{private:
	Texture invTexture;
	Texture qInvTexture;
	Texture invSTexture;
	Sprite qInvSprite;
	Sprite invSprite;
	Sprite invSSprite;
	FloatRect invSquare[44];
	Text itemQuantity[40];
	Text mouseItemQuantity;
	
	int qInvSelected;
	int invSelected;

	void initFont(Font& gameFont);
	void initTextures();
	void initSprites(RenderWindow& gameWindow);
	void updateInventory(RenderWindow& gameWindow);
	void updateQInventory(RenderWindow& gameWindow);
	void initInventory();


 public:
	 vector<pair<unique_ptr<Item>, int>> inv_vector;
	 pair<unique_ptr<Item>, int> mouseItem;
	 Inventory(RenderWindow& gameWindow, Font& gameFont);
	 void displayInventory(RenderWindow& gameWindow);
	 void displayQInventory(RenderWindow& gameWindow);
	 void qInvSelect(int selec);
	 void displayQInventorySelected(RenderWindow& gameWindow);
	 void displayInventorySelected(RenderWindow& gameWindow);
	 bool isInventoryFull(int id);
	 int getInventorySelected();
	 IDs getQInventorySelectedID();
	 int getQInventorySelected();
};

