#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Entity.h"
#include "Block.h"


class Player : public Entity
{
private:
	int x;
public:
	Player();
	void DestroyBlock(map<int, map<int, B>> &world);
	void Draw(RenderWindow& gameWindow);
};

