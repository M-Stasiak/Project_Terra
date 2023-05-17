#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
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
	int selected;

	void initTextures();
	void initSprites(RenderWindow& gameWindow);
	void updateInventory();
	void updateQInventory();

 public:
	 Inventory(RenderWindow& gameWindow);
	 void displayInventory(RenderWindow& gameWindow);
	 void displayQInventory(RenderWindow& gameWindow);
	 void qInvSelect(int selec);
	 void displayQInventorySelected(RenderWindow& gameWindow);

};

