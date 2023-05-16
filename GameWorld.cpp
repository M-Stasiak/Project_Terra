#include "GameWorld.h"

GameWorld::GameWorld()
{
	sf::Texture t1;
	t1.loadFromFile("Textures/tileset.png");
	Block block1(t1, { 15, 15, 18, 18 }, sf::Vector2f(0, 0));

	/*for (int i = 0; i < 100; i++)
	{
		vector<Block*> pom;
		for (int j = 0; j < 100; j++)
		{
			pom.push_back(new Block(t1, { 15, 15, 18, 18 }, sf::Vector2f(i*20, j*20)));
		}
		world.push_back(pom);
	}*/
	/*for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			world.push_back(new Block(t1, { 15, 15, 18, 18 }, sf::Vector2f(i * 20, j * 20)));
		}
	}*/
	for (int i = 0; i < 8000; i++)
	{
		vector<IDs> pom;
		for (int j = 0; j < 10; j++)
		{
			pom.push_back(IDs::Air);
		}
		for (int j = 10; j < 6000; j++)
		{
			pom.push_back(IDs::Grass);
		}
		world.push_back(pom);
	}
}