#include "Skeleton.h"

Skeleton::Skeleton()
{
	Texture entityTexture;
	entityTexture.loadFromFile("Textures/Entities/Skeleton.png");
	setEntity(entityTexture, { {4, 0, 300, 150, 150}, {4, 0, 750, 150, 150}, { 25, 50, -50, -100 } });
	animations[AnimationName::Attack] = new Animation(entityTexture, vector<int>{ 8, 0, 0, 150, 150 }, vector<int>{ 25, 50, -50, -100 });
	animations[AnimationName::Damage] = new Animation(entityTexture, vector<int>{ 4, 0, 600, 150, 150 }, vector<int>{ 25, 50, -50, -100 });
	animations[AnimationName::Death] = new Animation(entityTexture, vector<int>{ 4, 0, 150, 150, 150 }, vector<int>{ 25, 50, -50, -100 });
	origin.x = 50; origin.y = 25;
	setOrigin(origin);
	speed = 100;
	health = 200;
	maxHealth = 200;
	healthBar.setHealthBar(health, maxHealth);
	bufferStep.loadFromFile("Textures/step.wav");
	bufferJump.loadFromFile("Textures/jump.wav");
	bufferLand.loadFromFile("Textures/land.wav");
	bufferAttack.loadFromFile("Textures/attack.wav");
	bufferDamage.loadFromFile("Textures/skeletonHit.wav");
	soundStep.setBuffer(bufferStep);
	soundJump.setBuffer(bufferJump);
	soundLand.setBuffer(bufferLand);
	soundAttack.setBuffer(bufferAttack);
	soundDamage.setBuffer(bufferDamage);
}

void Skeleton::Draw(RenderWindow& gameWindow)
{
	gameWindow.draw(*this);
	healthBar.Draw(gameWindow, health, this->getGlobalBounds());
}

void Skeleton::UpdateAI(float elapsed, Entity& player, map<int, map<int, B>>& world)
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