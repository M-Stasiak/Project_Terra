#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Entity.h"


class Player : public Entity
{
private:
	int x;
public:
	Player();
	void Draw(RenderWindow& gameWindow);
};

