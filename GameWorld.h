#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <map>
#include <iostream>
#include "Block.h"
#include "Item.h"
#include "Block_Item.h"


using namespace std;

class GameWorld
{
public:
	map<int, map<int, B>> world;
	vector<Item*> items_on_ground;

public:
	GameWorld();
	void dropItem(IDs id, map <IDs, sf::Texture*>& arg, Vector2f pos);
	void drawItemsOnGround(RenderWindow& gameWindow);
};

