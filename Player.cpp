#include "Player.h"

Player::Player()
{
	Texture entityTexture;
	entityTexture.loadFromFile("Textures/adventurer.png");
	setEntity(entityTexture, { {4, 0, 0, 50, 37}, {6, 50, 37, 50, 37} });
	setOrigin(25, 18.5);
}

void Player::Draw(RenderWindow &gameWindow)
{
	gameWindow.draw(*this);
}