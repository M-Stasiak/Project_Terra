#include "Blocks.h"

void prepareBlocksTextures(std::map <IDs, sf::Texture*> &arg)
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
	arg[IDs::CraftingTableID] = tileset;
	arg[IDs::ClayID] = tileset;
	arg[IDs::BricksID] = tileset;
	arg[IDs::HayID] = tileset;

	sf::Texture* tileset2 = new sf::Texture;
	tileset2->loadFromFile("Textures/Destructible Objects Sprite Sheet.png");
	arg[IDs::ChestID] = tileset2;
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
	arg1[IDs::ChestID] = new Chest(arg2);
	arg1[IDs::CraftingTableID] = new CraftingTable(arg2);
	arg1[IDs::ClayID] = new Clay(arg2);
	arg1[IDs::BricksID] = new Bricks(arg2);
	arg1[IDs::HayID] = new Hay(arg2);

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
	dropID = IDs::StickID;
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

Chest::Chest(std::map <IDs, sf::Texture*>& arg)
{
	ID = IDs::ChestID;
	dropID = IDs::ChestID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(24, 727, 17, 16));
	scale(0.95, 1);
	
}

CraftingTable::CraftingTable(std::map<IDs, sf::Texture*>& arg)
{
	ID = IDs::CraftingTableID;
	dropID = IDs::CraftingTableID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(48, 224, 16, 16));

}

Clay::Clay(std::map<IDs, sf::Texture*>& arg)
{
	ID = IDs::ClayID;
	dropID = IDs::ClayID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(96, 96, 16, 16));

}

Bricks::Bricks(std::map<IDs, sf::Texture*>& arg)
{
	ID = IDs::BricksID;
	dropID = IDs::BricksID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(160, 48, 16, 16));

}

Hay::Hay(std::map<IDs, sf::Texture*>& arg)
{
	ID = IDs::HayID;
	dropID = IDs::HayID;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(256, 240, 16, 16));

}
