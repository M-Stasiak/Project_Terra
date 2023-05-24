#include "Blocks.h"

void prepareTextures(std::map <IDs, sf::Texture*> &arg)
{
	sf::Texture* tileset = new sf::Texture;
	tileset->loadFromFile("Textures/Tileset.png");
	arg[IDs::GrassID] = tileset;
	arg[IDs::DirtID] = tileset;
}

void prepareBlocksMap(std::map<IDs, Block*> &arg1, std::map <IDs, sf::Texture*> &arg2)
{
	arg1[IDs::GrassID] = new Grass(arg2);
	arg1[IDs::DirtID] = new Dirt(arg2);
}

Grass::Grass(std::map <IDs, sf::Texture*> &arg)
{
	ID = IDs::GrassID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(32, 464, 16, 16));
}

IDs Grass::getDropID()
{
	return dropID;
}

Dirt::Dirt(std::map <IDs, sf::Texture*>& arg)
{
	ID = IDs::DirtID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(32, 480, 16, 16));
}

IDs Dirt::getDropID()
{
	return dropID;
}
