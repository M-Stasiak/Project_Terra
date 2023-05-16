#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Block.h"

using namespace std;

class GameWorld
{
public:
	//vector<vector<Block*>> world;
	vector<vector<IDs>> world;
	//vector<Block*> world;

public:
	GameWorld();
};

