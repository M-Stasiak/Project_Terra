#include "Zombie.h"

Zombie::Zombie()
{
	Texture entityTexture;
	entityTexture.loadFromFile("Textures/Entities/Zombie.png");
	setEntity(entityTexture, { {8, 0, 0, 32, 32}, {8, 0, 64, 32, 32} });
	animations[AnimationName::Attack] = new Animation(entityTexture, vector<int>{ 7, 0, 32, 32, 32 }, vector<int>{ 0, 0, 0, 0 });
	animations[AnimationName::Damage] = new Animation(entityTexture, vector<int>{ 3, 0, 160, 32, 32 }, vector<int>{ 0, 0, 0, 0 });
	animations[AnimationName::Death] = new Animation(entityTexture, vector<int>{ 6, 64, 160, 32, 32 }, vector<int>{ 0, 0, 0, 0 });
	origin.x = 16; origin.y = 16;
	setOrigin(origin);
	speed = 100;
}

void Zombie::Draw(RenderWindow& gameWindow)
{
	gameWindow.draw(*this);
	healthBar.Draw(gameWindow, health, this->getGlobalBounds());
}

void Zombie::UpdateAI(float elapsed, Entity& player, map<int, map<int, B>>& world)
{
	if (isAlive and player.getIsAlive())
	{
		if (player.getPosition().x + 10 > getPosition().x and player.getPosition().x - 10 < getPosition().x)
		{
			if (player.getGlobalBounds().intersects(getGlobalBounds()))
				Attack(elapsed, player);
		}
		else
		{
			if (player.getPosition().x - 10 > getPosition().x)
				Right(elapsed);
			else if (player.getPosition().x + 10 < getPosition().x)
				Left(elapsed);

			if (getScale().x > 0 and world[(getGlobalBounds().left + getGlobalBounds().width) / 16 + 1][(getGlobalBounds().top + getGlobalBounds().height - 8) / 16].ID != IDs::AirID and world[(getGlobalBounds().left + getGlobalBounds().width) / 16 + 1][(getGlobalBounds().top + getGlobalBounds().height - 8) / 16].rect.width != 0)
				Up(elapsed);
			else if (getScale().x < 0 and world[(getGlobalBounds().left) / 16 - 1][(getGlobalBounds().top + getGlobalBounds().height - 8) / 16].ID != IDs::AirID and world[(getGlobalBounds().left) / 16 - 1][(getGlobalBounds().top + getGlobalBounds().height - 8) / 16].rect.width != 0)
				Up(elapsed);
		}
	}
}