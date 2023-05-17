#include "GameWorld.h"

GameWorld::GameWorld(sf::Texture& t, sf::Vector2f playerPosition)
{
	for (int i = 0; i < 1000; i++)
	{
		map<int, B> pom;
		for (int j = 0; j < 10; j++)
		{
			sf::FloatRect p(i * 16, j * 16, 0, 0);
			B a(IDs::Air, p);
			pom[j] = a;
		}
		for (int j = 10; j < 1000; j++)
		{
			sf::FloatRect p(i * 16, j * 16, 16, 16);
			B a(IDs::Grass, p);
			pom[j] = a;
		}
		world[i] = pom;
	}
}