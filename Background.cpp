#include "Background.h"

void Background::initTextures()
{
	string pathName = "Textures/background_layer_";
	for (int i = 0; i < 3; i++)
	{
		background_layers_textures.push_back(new Texture);
		background_layers_textures.back()->loadFromFile(pathName + to_string(i+1) + ".png");
		background_layers_textures.back()->setRepeated(true);
	}

	pathName = "Textures/grey_L";
	for (int i = 0; i < 4; i++)
	{
		background_layers_textures.push_back(new Texture);
		background_layers_textures.back()->loadFromFile(pathName + to_string(i + 1) + ".png");
		background_layers_textures.back()->setRepeated(true);
	}
}

void Background::initSprites()
{
	vector<Sprite*> pom;
	for (int i = 0; i < 3; i++)
	{
		pom.push_back(new Sprite);
		pom.back()->setTexture(*background_layers_textures[i]);
		pom.back()->setTextureRect(IntRect(0, 0, 16 * 1000, background_layers_textures[i]->getSize().y));
		pom.back()->setScale(3, 3);
	}
	background_layers.push_back(pom);

	pom.clear();
	for (int i = 3; i < 7; i++)
	{
		pom.push_back(new Sprite);
		pom.back()->setTexture(*background_layers_textures[i]);
		pom.back()->setTextureRect(IntRect(0, 0, 16 * 1000, background_layers_textures[i]->getSize().y));
		pom.back()->setScale(2, 2);
	}
	background_layers.push_back(pom);
}

Background::Background()
{
	initTextures();
	initSprites();
}

void Background::Render(RenderWindow& gameWindow)
{
	int height = 250*16, heightpom = 5*16;
	float x = 0;
	if (gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).y < height)
	{
		for (auto i : background_layers[0])
		{
			i->setPosition(gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).x / (1.2 + x), gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).y);
			gameWindow.draw(*i);

			x += 0.2;
		}
	}
	else if (gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).y > height and gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).y < height+heightpom)
	{
		for (auto i : background_layers[0])
		{
			i->setPosition(gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).x / (1.2 + x), gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).y);
			gameWindow.draw(*i);

			x += 0.2;
		}
		x = 0;
		for (auto i : background_layers[1])
		{
			i->setPosition(gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).x / (1.2 + x), gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).y);
			i->setColor(Color(255, 255, 255, (gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).y-height)/heightpom * 255));
			gameWindow.draw(*i);

			x += 0.2;
		}
	}
	else
	{
		for (auto i : background_layers[1])
		{
			i->setPosition(gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).x / (1.2 + x), gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView()).y);
			gameWindow.draw(*i);

			x += 0.2;
		}
	}
}