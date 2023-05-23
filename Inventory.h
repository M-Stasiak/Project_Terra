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
	FloatRect invSquare[44];
	int selected;
	bool invSelected;

	void initTextures();
	void initSprites(RenderWindow& gameWindow);
	void initSquares();
	void updateInventory(RenderWindow& gameWindow);
	void updateQInventory(RenderWindow& gameWindow);

 public:
	 Inventory(RenderWindow& gameWindow);
	 void displayInventory(RenderWindow& gameWindow);
	 void displayQInventory(RenderWindow& gameWindow);
	 void qInvSelect(int selec);
	 void displayQInventorySelected(RenderWindow& gameWindow);
	 void displayInventorySelected(RenderWindow& gameWindow);

};

