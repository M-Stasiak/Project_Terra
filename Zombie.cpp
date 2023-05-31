#include "Zombie.h"

Zombie::Zombie()
{
	Texture entityTexture;
	entityTexture.loadFromFile("Textures/Entities/ZombieSpriteSheet.png");
	setEntity(entityTexture, { {5, 352, 64, 32, 32}, {10, 0, 64, 32, 32} });
	origin.x = 16; origin.y = 16;
	setOrigin(origin);
	speed = 100;
}

void Zombie::Draw(RenderWindow& gameWindow)
{
	gameWindow.draw(*this);
}

void Zombie::UpdateAI(float elapsed, Entity& player, map<int, map<int, B>>& world)
{
	if (player.getPosition().x - 10 > getPosition().x)
		Right(elapsed);
	else if (player.getPosition().x + 10 < getPosition().x)
		Left(elapsed);

	if (getScale().x > 0 and world[getPosition().x / 16 + 2][getPosition().y / 16].ID != IDs::AirID)
		Up(elapsed);
	else if (getScale().x < 0 and world[getPosition().x / 16 - 2][getPosition().y / 16].ID != IDs::AirID)
		Up(elapsed);

	if (this->getGlobalBounds().intersects(player.getGlobalBounds()))
	{
		Attack(elapsed, player);
	}
}