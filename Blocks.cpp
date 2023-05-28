#include "Blocks.h"

void prepareTextures(std::map <IDs, sf::Texture*> &arg)
{
	sf::Texture* tileset = new sf::Texture;
	tileset->loadFromFile("Textures/Tileset.png");
	arg[IDs::GrassID] = tileset;
	arg[IDs::DirtID] = tileset;
	arg[IDs::RockID] = tileset;
	arg[IDs::WoodID] = tileset;
	arg[IDs::PlankID] = tileset;
	arg[IDs::LeavesID] = tileset;
	arg[IDs::CactusID] = tileset;
	arg[IDs::SandID] = tileset;
}

void prepareBlocksMap(std::map<IDs, Block*> &arg1, std::map <IDs, sf::Texture*> &arg2)
{
	arg1[IDs::GrassID] = new Grass(arg2);
	arg1[IDs::DirtID] = new Dirt(arg2);
	arg1[IDs::RockID] = new Rock(arg2);
	arg1[IDs::WoodID] = new Wood(arg2);
	arg1[IDs::PlankID] = new Plank(arg2);
	arg1[IDs::LeavesID] = new Leaves(arg2);
	arg1[IDs::CactusID] = new Cactus(arg2);
	arg1[IDs::SandID] = new Sand(arg2);
}

Grass::Grass(std::map <IDs, sf::Texture*> &arg)
{
	ID = IDs::GrassID;
	dropID = IDs::DirtID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(48, 464, 16, 16));
}

Dirt::Dirt(std::map <IDs, sf::Texture*>& arg)
{
	ID = IDs::DirtID;
	dropID = IDs::DirtID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(48, 480, 16, 16));
}

Rock::Rock(std::map <IDs, sf::Texture*>& arg)
{
	ID = IDs::RockID;
	dropID = IDs::RockID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(48, 32, 16, 16));
}

Wood::Wood(std::map <IDs, sf::Texture*>& arg)
{
	ID = IDs::WoodID;
	dropID = IDs::WoodID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(208, 192, 16, 16));
}

Plank::Plank(std::map <IDs, sf::Texture*>& arg)
{
	ID = IDs::PlankID;
	dropID = IDs::PlankID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(16, 208, 16, 16));
}

Leaves::Leaves(std::map <IDs, sf::Texture*>& arg)
{
	ID = IDs::LeavesID;
	dropID = IDs::LeavesID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(0, 256, 16, 16));
}

Cactus::Cactus(std::map <IDs, sf::Texture*>& arg)
{
	ID = IDs::CactusID;
	dropID = IDs::CactusID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(304, 240, 16, 16));
}

Sand::Sand(std::map <IDs, sf::Texture*>& arg)
{
	ID = IDs::SandID;
	dropID = IDs::SandID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(16, 96, 16, 16));
}
