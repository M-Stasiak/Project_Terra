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

GameWorld::GameWorld()
{
	/*for (int i = 0; i < 1000; i++)
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
	}*/

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
				if (idInt == 0) idInt++;
				IDs xd = static_cast<IDs>(idInt);
				sf::FloatRect p(i * 16, j * 16, 16, 16);
				B a(xd, p);
				pom[j] = a;
				idInt++;
				if (idInt > ChestID) idInt = AirID;
			}
		}
		/*for (int j = 0; j < 1000; j++)
		{
			if (j < (int)y[i])
			{
				sf::FloatRect p(i * 16, j * 16, 16, 16);
				B a(IDs::AirID, p);
				pom[j] = a;
			}
			else if (j > (int)y[i])
			{
				sf::FloatRect p(i * 16, j * 16, 16, 16);
				B a(IDs::DirtID, p);
				pom[j] = a;
			}
		}*/
		world[i] = pom;
	}

	//vector<float> xw = {1101.0, 911.3, 636.0, 451.1 };
	//vector<float> yw = {25.113, 30.131, 40.120, 50.128 };

	//vector<float> x = { 400, 480, 560, 640, 720, 800, 880, 960, 1040, 1120, 1200 };
	//vector<float> y = Interpolation(xw, yw, x);
	//for (int i = 0; i < x.size(); i++)
	//	cout << x[i] << " " << y[i] << endl;

	//world = rotateMap(world);
}

void GameWorld::dropItem(IDs id, map <IDs, sf::Texture*>& arg1, map <IDs, Block*>& arg2, Vector2f pos)
{
	if (id != 0 && id<=10){
	items_on_ground.emplace_back(new Block_Item(arg1, arg2, id, pos));
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
