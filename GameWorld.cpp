#include "GameWorld.h"

template <typename T> vector<vector<T>> DividedDifferences(vector<T> x, vector<T> y)
{
	vector<vector<T>> result(x.size());
	for (int i = 0; i < x.size(); i++)
	{
		vector<T> pom(x.size(), 0);
		pom[0] = y[i];
		result[i] = pom;
	}

	for (int j = 1; j < x.size(); j++)
		for (int i = j; i < x.size(); i++)
			result[i][j] = (result[i][j - 1] - result[i - 1][j - 1]) / (x[i] - x[i - j]);

	return result;
}

template <typename T> T f(vector<vector<T>> c, vector<T> xw, T x)
{
	T result = 0;
	vector<T> pom(c.size()+1);
	pom[0] = 1;
	for (int i = 0; i < c.size(); i++)
	{
		pom[i + 1] = (x - xw[i]) * pom[i];
		result = result + c[i][i] * pom[i];
	}

	return result;
}

template <typename T> vector<T> Interpolation(vector<T> xw, vector<T> yw, vector<T> x)
{
	vector<vector<T>> c = DividedDifferences(xw, yw);
	vector<T> result(x.size());
	for (int i = 0; i < x.size(); i++)
		result[i] = f(c, xw, x[i]);

	return result;
}

void GameWorld::GenerateTree(int i, int j)
{
	int height = rand() % 7 + 4;
	int radius = rand() % 7 + 5;
	for (int k = 0; k < height; k++)
	{
		sf::FloatRect p(i * 16, (j-k) * 16, 0, 0);
		B a(IDs::WoodID, p);
		world[i][j - k] = a;
	}
	for (int k = i - radius; k < i + radius; k++)
	{
		for (int l = j - radius; l < j + radius; l++)
		{
			if ((k - i) * (k - i) + (l - j) * (l - j) <= radius)
			{
				sf::FloatRect p(k * 16, (l-height) * 16, 0, 0);
				B a(IDs::LeavesID, p);
				world[k][l-height] = a;
			}
		}
	}
}

GameWorld::GameWorld()
{
	unsigned int width = 1000, height = 1000;

	int idInt = AirID;
	srand(time(NULL));
	vector<float> xw, yw, x, y;
	for (int i = 0; i <= 1000; i += 100)
	{
		xw.push_back(i);
		yw.push_back(rand() % 10+200);
	}

	for (int i = 0; i < 1000; i++)
	{
		x.push_back(i);
	}
	y = Interpolation(xw, yw, x);

	PerlinNoise pn1(rand());
	PerlinNoise ironPn(rand());
	PerlinNoise goldPn(rand());
	PerlinNoise diamondPn(rand());

	for (int i = 0; i < y.size(); i++)
	{
		map<int, B> pom;
		sf::FloatRect p(i * 16, (int)y[i] * 16, 16, 16);
		B a(IDs::GrassID, p);
		pom[(int)y[i]] = a;
		for (int j = 0; j < y.size(); j++)
		{
			if (j < (int)y[i])
			{
				sf::FloatRect p(i * 16, j * 16, 0, 0);
				B a(IDs::AirID, p);
				pom[j] = a;
			}
			else if (j > (int)y[i])
			{
				// New Procedural Generator
				double xPom = (double)j / ((double)width);
				double yPom = (double)i / ((double)height);

				double n1 = pn1.noise(100 * xPom, 100 * yPom, 0.8);
				double n2 = ironPn.noise(100 * xPom, 100 * yPom, 0.8);
				double n3 = goldPn.noise(100 * xPom, 100 * yPom, 0.2);
				double n4 = diamondPn.noise(100 * xPom, 100 * yPom, 0.001);

				if (n1 > 0.4)
				{
					if (n4 < 0.2 and j >(int)y[i] + 300)
					{
						sf::FloatRect p(i * 16, j * 16, 16, 16);
						B a(IDs::DiamondID, p);
						pom[j] = a;
					}
					else if (n3 < 0.3 and j >(int)y[i] + 100)
					{
						sf::FloatRect p(i * 16, j * 16, 16, 16);
						B a(IDs::GoldID, p);
						pom[j] = a;
					}
					else if (n2 < 0.3)
					{
						sf::FloatRect p(i * 16, j * 16, 16, 16);
						B a(IDs::IronID, p);
						pom[j] = a;
					}
					else
					{
						if (j > (int)y[i] + 20)
						{
							sf::FloatRect p(i * 16, j * 16, 16, 16);
							B a(IDs::RockID, p);
							pom[j] = a;
						}
						else
						{
							sf::FloatRect p(i * 16, j * 16, 16, 16);
							B a(IDs::DirtID, p);
							pom[j] = a;
						}
					}
				}
				else
				{
					sf::FloatRect p(i * 16, j * 16, 0, 0);
					B a(IDs::AirID, p);
					pom[j] = a;
				}
				// End Procedural Generator

				/*if (idInt == 0) idInt++;
				IDs xd = static_cast<IDs>(idInt);
				sf::FloatRect p(i * 16, j * 16, 16, 16);
				B a(xd, p);
				pom[j] = a;
				idInt++;
				if (idInt > HayID) idInt = AirID;*/
			}
		}
		world[i] = pom;
	}

	for (int i = 10; i < 990; i+=10)
	{
		if (rand()%10 > 4) GenerateTree(i, (int)y[i]-1);
	}
}

void GameWorld::test(RenderWindow& gameWindow)
{
	unsigned int width = 192, height = 108;

	static unsigned int seed = 0;
	seed++;
	PerlinNoise pn(seed);
	RectangleShape kw(Vector2f(10, 10));

	for (unsigned int i = 0; i < height; ++i) 
	{     // y
		for (unsigned int j = 0; j < width; ++j) 
		{  // x
			double x = (double)j / ((double)width);
			double y = (double)i / ((double)height);

			double n = pn.noise(10 * x, 10 * y, 0.8);

			// Wood like structure
			//n = 20 * pn.noise(x, y, 0.8);
			//n = n - floor(n);

			kw.setPosition(j * 10, i * 10);
			//kw.setFillColor(Color(255, 255, 255, floor(255 * n)));
			if (n > 0.4) kw.setFillColor(Color::Black);
			else kw.setFillColor(Color::White);
			gameWindow.draw(kw);
		}
	}
}

void GameWorld::dropItem(IDs id, map <IDs, sf::Texture*>& arg1, map <IDs, Texture*>& arg2, map <IDs, Block*>& arg3, map <IDs, Item*>& arg4, Vector2f pos)
{
	if (id != 0 && id<= FurnaceID){
	items_on_ground.emplace_back(new Block_Item(arg1, arg3, id, pos));
	}
	else if (id != 0 && id >= WoodenSwordID && id <= StonePickaxeID) {
		items_on_ground.emplace_back(new Tool_Item(id, arg2, arg4, pos));
	}
	else if (id != 0 && id >= StickID) {
	items_on_ground.emplace_back(new Material_Item(id,arg2, arg4, pos));
	}
	
}

void GameWorld::drawItemsOnGround(RenderWindow& gameWindow, Vector2f playerPosition, int renderWidth, int renderHeight)
{
	for (auto &&item : items_on_ground) {
		if (item->getPosition().x > playerPosition.x - renderWidth * 16 and item->getPosition().x < playerPosition.x + renderWidth * 16 and item->getPosition().y > playerPosition.y - renderHeight * 16 and item->getPosition().y < playerPosition.y + renderHeight * 16)
		{
			gameWindow.draw(*item);
		}
		
	}
}

bool GameWorld::checkWorld(int _i, int _j, int r)
{
	for (int i = _i - r; i < _i + r; i++)
	{
		for (int j = _j - r; j < _j + r; j++)
		{
			if (world[i][j].ID != AirID)
				return false;
		}
	}
	return true;
}

void GameWorld::GenerateEntities(float elapsed, Entity& player, vector<Entity*>& entities)
{
	if (entities.size() < 50)
	{
		zombieTime += elapsed; skeletonTime += elapsed; mushroomTime += elapsed; slimeTime += elapsed;

		if (zombieTime > 20)
		{
			int randPom = rand() % 100;

			if (randPom < 50)
			{
				if (player.getPosition().x - 50 > 0)
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x - 50, pom, 3)) pom--;
					entities.push_back(new Zombie);
				}
				else
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x + 50, pom, 3)) pom--;
					entities.push_back(new Zombie);
				}
			}
			else
			{
				if (player.getPosition().x + 50 < 16 * 1000)
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x + 50, pom, 3)) pom--;
					entities.push_back(new Zombie);
				}
				else
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x - 50, pom, 3)) pom--;
					entities.push_back(new Zombie);
				}
			}
			zombieTime = 0;
		}

		if (slimeTime > 10)
		{
			int randPom = rand() % 100;

			if (randPom < 50)
			{
				if (player.getPosition().x - 50 > 0)
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x - 50, pom, 3)) pom--;
					entities.push_back(new Slime);
				}
				else
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x + 50, pom, 3)) pom--;
					entities.push_back(new Slime);
				}
			}
			else
			{
				if (player.getPosition().x + 50 < 16 * 1000)
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x + 50, pom, 3)) pom--;
					entities.push_back(new Slime);
				}
				else
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x - 50, pom, 3)) pom--;
					entities.push_back(new Slime);
				}
			}
			slimeTime = 0;
		}

		if (skeletonTime > 40)
		{
			int randPom = rand() % 100;

			if (randPom < 50)
			{
				if (player.getPosition().x - 50 > 0)
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x - 50, pom, 5)) pom--;
					entities.push_back(new Skeleton);
				}
				else
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x + 50, pom, 5)) pom--;
					entities.push_back(new Skeleton);
				}
			}
			else
			{
				if (player.getPosition().x + 50 < 16 * 1000)
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x + 50, pom, 5)) pom--;
					entities.push_back(new Skeleton);
				}
				else
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x - 50, pom, 5)) pom--;
					entities.push_back(new Skeleton);
				}
			}
			skeletonTime = 0;
		}

		if (mushroomTime > 40)
		{
			int randPom = rand() % 100;

			if (randPom < 50)
			{
				if (player.getPosition().x - 50 > 0)
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x - 50, pom, 5)) pom--;
					entities.push_back(new Mushroom);
				}
				else
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x + 50, pom, 5)) pom--;
					entities.push_back(new Mushroom);
				}
			}
			else
			{
				if (player.getPosition().x + 50 < 16 * 1000)
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x + 50, pom, 5)) pom--;
					entities.push_back(new Mushroom);
				}
				else
				{
					int pom = player.getPosition().y;
					while (checkWorld(player.getPosition().x - 50, pom, 5)) pom--;
					entities.push_back(new Mushroom);
				}
			}
			mushroomTime = 0;
		}
	}
}
