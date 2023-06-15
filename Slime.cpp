#include "Slime.h"

Slime::Slime()
{
	Texture entityTexture;
	entityTexture.loadFromFile("Textures/Entities/Slime.png");
	setEntity(entityTexture, { {4, 32, 0, -32, 25}, {4, 160, 0, -32, 25} });
	animations[AnimationName::Attack] = new Animation(entityTexture, vector<int>{ 5, 32, 25, -32, 25 }, vector<int>{ 0, 0, 0, 0 });
	animations[AnimationName::Damage] = new Animation(entityTexture, vector<int>{ 3, 192, 25, -32, 25 }, vector<int>{ 0, 0, 0, 0 });
	animations[AnimationName::Death] = new Animation(entityTexture, vector<int>{ 5, 32, 50, -32, 25 }, vector<int>{ 0, 0, 0, 0 });
	origin.x = 16; origin.y = 12.5;
	setOrigin(origin);
	speed = 50;
	health = 20;
	maxHealth = 20;
	healthBar.setHealthBar(health, maxHealth);
	healthBar.setHealthBar(health, maxHealth);
	bufferAttack.loadFromFile("Textures/slimeHit.wav");
	bufferDamage.loadFromFile("Textures/slimeDamage.wav");
	soundAttack.setBuffer(bufferAttack);
	soundDamage.setBuffer(bufferDamage);
}

void Slime::Draw(RenderWindow& gameWindow)
{
	gameWindow.draw(*this);
	healthBar.Draw(gameWindow, health, this->getGlobalBounds());
}

void Slime::UpdateAI(float elapsed, Entity& player, map<int, map<int, B>>& world)
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