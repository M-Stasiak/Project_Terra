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
	vector<unique_ptr<I>> items_on_ground;

public:
	GameWorld();
	void dropItem(IDs id, Vector2f pos);
	void drawItemsOnGround(RenderWindow& gameWindow, map <IDs, Item*>& items, Vector2f playerPosition, int renderWidth, int renderHeight);
};

