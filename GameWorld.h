#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <map>
#include "Block.h"

using namespace std;

class GameWorld
{
public:
	map<int, map<int, B>> world;

public:
	GameWorld();
};

