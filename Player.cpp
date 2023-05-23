#include "Player.h"



Player::Player()
{
	Texture entityTexture;
	entityTexture.loadFromFile("Textures/adventurer.png");
	setEntity(entityTexture, { {4, 0, 0, 50, 37}, {6, 50, 37, 50, 37} });
	origin.x = 25; origin.y = 18.5;
	setOrigin(origin);
}


void Player::Draw(RenderWindow &gameWindow)
{
	gameWindow.draw(*this);
}