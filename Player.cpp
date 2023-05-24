#include "Player.h"



Player::Player()
{
	Texture entityTexture;
	entityTexture.loadFromFile("Textures/adventurer.png");
	setEntity(entityTexture, { {4, 0, 0, 50, 37}, {6, 50, 37, 50, 37} });
	origin.x = 25; origin.y = 18.5;
	setOrigin(origin);
}

void Player::DestroyBlock(map<int, map<int, B>> &world)
{
	cout << getPosition().x << " " << getPosition().y << endl;
	cout << Mouse::getPosition().x + getPosition().x - (VideoMode::getDesktopMode().width) * 0.5 <<" "<< Mouse::getPosition().y + getPosition().y - (VideoMode::getDesktopMode().height) * 0.5 <<" Destroy" << endl;
	sf::FloatRect p((int)Mouse::getPosition().x + getPosition().x - VideoMode::getDesktopMode().width * 0.5, (int)Mouse::getPosition().y + getPosition().y - VideoMode::getDesktopMode().height * 0.5, 0, 0);
	B a(IDs::AirID, p);
	world[(Mouse::getPosition().x + getPosition().x - VideoMode::getDesktopMode().width * 0.5) / 16][(Mouse::getPosition().y + getPosition().y - VideoMode::getDesktopMode().height * 0.5) / 16] = a;
}


void Player::Draw(RenderWindow &gameWindow)
{
	gameWindow.draw(*this);
}