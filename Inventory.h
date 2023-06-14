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
{
private:
	Texture invTexture;
	Texture qInvTexture;
	Texture invSTexture;
	Texture craftingSlotTexture;
	Texture requiredBackground;
	Texture y_n;
	Texture chestTexture;
	Sprite no_yes;
	Sprite isAbleToCraftYN;
	vector<unique_ptr<Sprite>> slotSprites;
	vector<unique_ptr<Item>> itemsRequiredToCraft;
	vector<unique_ptr<Text>> itemsRequiredToCraftQuantity;
	Sprite qInvSprite;
	Sprite invSprite;
	Sprite invSSprite;
	Sprite craftingSelectedSprite;
	Sprite reqBackground;
	Sprite chestSprite;
	Text craftedItemQuantity;
	Text itemsRequired;
	Text chest;
	FloatRect invSquare[44];
	FloatRect chestSquare[24];
	Text itemQuantity[40];
	Text chestItemQuantity[24];
	
	unique_ptr<Item> craftingTableRequired;
	
	int qInvSelected;
	int invSelected;
	int craftSelected;
	int mouseOnCraft;
	bool mouseOnCrafting;
	bool isCraftingTableNear;
	int chestSelected;

	void initFont(Font& gameFont);
	void initTextures();
	void initSprites(RenderWindow& gameWindow);
	void initTexts();
	void updateInventory(RenderWindow& gameWindow, bool chestOpened);
	void updateQInventory(RenderWindow& gameWindow);
	void initInventory(map <IDs, sf::Texture*>& arg1, map <IDs, sf::Texture*>& arg4,map <IDs, Block*>& arg2, map <IDs, Item*>& arg3, Font& gameFont);
	void craftSelect(RenderWindow& gameWindow);


 public:
	 unique_ptr<Item> selectedItem;
	 vector<pair<unique_ptr<Item>, int>> inv_vector;
	 pair<unique_ptr<Item>, int> mouseItem;
	 vector<unique_ptr<Item>> itemsToCraft;
	 Text mouseItemQuantity;
	 Inventory(RenderWindow& gameWindow, Font& gameFont, map <IDs, sf::Texture*>& arg1, map <IDs, sf::Texture*>& arg4, map <IDs, Block*>& arg2, map <IDs, Item*>& arg3);
	 void displayInventory(RenderWindow& gameWindow, bool chestOpened);
	 void displayQInventory(RenderWindow& gameWindow);
	 void qInvSelect(int selec);
	 void displayQInventorySelected(RenderWindow& gameWindow);
	 void displayInventorySelected(RenderWindow& gameWindow,bool chestOpened);
	 bool isInventoryFull(int id);
	 int getInventorySelected();
	 IDs getQInventorySelectedID();
	 int getQInventorySelected();
	 int getMouseOnCraft();
	 void setCraftSelected(int s, map <IDs, sf::Texture*>& arg1, map <IDs, sf::Texture*>& arg3, map <IDs, Block*>& arg2, map <IDs, Item*>& arg4, Font& gameFont);
	 bool isMouseOnCrafitng();
	 void checkSelectedItem();
	 bool isAbleToCraft();
	 int getCraftSelected();
	 void setIsCraftingTableNear(bool i);
	 int getSelectedToolBlockDamage();
	 int getChestSelected();
	 bool isMouseOnInventory(RenderWindow& gameWindow);
	 bool isMouseOnChest(RenderWindow& gameWindow);
	 Vector2f getChestItemsPosition(int i);
	 Text getChestItemQuantityText(int i);
	 void setChestItemQuantityTextPosition(Vector2f vec, int i);
	 void setChestItemQuantityTextString(string a, int i);
	 void setChestItemQuantityTextScale(float x, float y, int i);
	 bool isMouseOnCraftingRequired(RenderWindow& gameWindow);
	 
};

