#include "GameWorld.h"

GameWorld::GameWorld()
{
	for (int i = 0; i < 1000; i++)
	{
		map<int, B> pom;
		for (int j = 0; j < 10; j++)
		{
			sf::FloatRect p(i * 16, j * 16, 0, 0);
			B a(IDs::AirID, p);
			pom[j] = a;
		}
		sf::FloatRect p(i * 16, 10 * 16, 16, 16);
		B a(IDs::DirtID, p);
		pom[10] = a;
		for (int j = 11; j < 1000; j++)
		{
			sf::FloatRect p(i * 16, j * 16, 16, 16);
			B a(IDs::GrassID, p);
			pom[j] = a;
		}
		world[i] = pom;
	}
}