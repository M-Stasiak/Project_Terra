#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Entity.h"
#include "Block.h"

class Slime : public Entity
{
public:
	Slime();
	void Draw(RenderWindow& gameWindow);

	void UpdateAI(float elapsed, Entity& player, map<int, map<int, B>>& world);
};

