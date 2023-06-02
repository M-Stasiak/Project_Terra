#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Item.h"
#include "Items.h";
#include <memory>
using namespace std;
using namespace sf;
class Inventory
{private:
	Texture invTexture;
	Texture qInvTexture;
	Texture invSTexture;
	Texture craftingSlotTexture;
	vector<unique_ptr<Sprite>> slotSprites;
	Sprite qInvSprite;
	Sprite invSprite;
	Sprite invSSprite;
	Sprite craftingSelectedSprite;
	Text craftingItemQuantity;
	FloatRect invSquare[44];
	Text itemQuantity[40];
	Text mouseItemQuantity;
	
	int qInvSelected;
	int invSelected;
	int craftSelected;
	int mouseOnCraft;
	bool mouseOnCrafting;

	void initFont(Font& gameFont);
	void initTextures();
	void initSprites(RenderWindow& gameWindow);
	void updateInventory(RenderWindow& gameWindow);
	void updateQInventory(RenderWindow& gameWindow);
	void initInventory(map <IDs, sf::Texture*>& arg1, map <IDs, Block*>& arg2);
	void craftSelect(RenderWindow& gameWindow);


 public:
	 vector<pair<unique_ptr<Item>, int>> inv_vector;
	 pair<unique_ptr<Item>, int> mouseItem;
	 vector<unique_ptr<Item>> itemsToCraft;
	 Inventory(RenderWindow& gameWindow, Font& gameFont, map <IDs, sf::Texture*>& arg1, map <IDs, Block*>& arg2);
	 void displayInventory(RenderWindow& gameWindow, map <IDs, sf::Texture*>& arg);
	 void displayQInventory(RenderWindow& gameWindow);
	 void qInvSelect(int selec);
	 void displayQInventorySelected(RenderWindow& gameWindow);
	 void displayInventorySelected(RenderWindow& gameWindow);
	 bool isInventoryFull(int id);
	 int getInventorySelected();
	 IDs getQInventorySelectedID();
	 int getQInventorySelected();
	 int getMouseOnCraft();
	 void setCraftSelected(int s);
	 bool isMouseOnCrafitng();
};

