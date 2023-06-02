#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <map>
#include <iostream>
#include "Block.h"
#include "Item.h"
#include "Items.h"


using namespace std;

class GameWorld
{
public:
	map<int, map<int, B>> world;
	vector<unique_ptr<Item>> items_on_ground;

public:
	GameWorld();
	void dropItem(IDs id, map <IDs, sf::Texture*>& arg1, map <IDs, Block*>& arg2, Vector2f pos);
	void drawItemsOnGround(RenderWindow& gameWindow, Vector2f playerPosition, int renderWidth, int renderHeight);
};

