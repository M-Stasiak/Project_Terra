#include "Block_Item.h"

void prepareItemsMap(std::map<IDs, Item*>& arg1, std::map <IDs, sf::Texture*>& arg2, map <IDs, Block*>& arg3)
{
    arg1[IDs::GrassID] = new Block_Item(arg2, arg3, IDs::GrassID);
    arg1[IDs::DirtID] = new Block_Item(arg2, arg3, IDs::DirtID);
    arg1[IDs::RockID] = new Block_Item(arg2, arg3, IDs::RockID);
    arg1[IDs::WoodID] = new Block_Item(arg2, arg3, IDs::WoodID);
    arg1[IDs::PlankID] = new Block_Item(arg2, arg3, IDs::PlankID);
    arg1[IDs::LeavesID] = new Block_Item(arg2, arg3, IDs::LeavesID);
    arg1[IDs::CactusID] = new Block_Item(arg2, arg3, IDs::CactusID);
    arg1[IDs::SandID] = new Block_Item(arg2, arg3, IDs::SandID);
    arg1[IDs::ChestID] = new Block_Item(arg2, arg3, IDs::ChestID);
}

Block_Item::Block_Item(map<IDs,Texture*>& arg1, map <IDs, Block*>& arg2, IDs id)
{
	ID = id;
	setTexture(*arg1[ID]);
	setTextureRect(arg2[ID]->getTextureRect());
	setScale(0.5, 0.5);
	stackingQuantity = 64;
}
int Block_Item::getStackingQuantity()
{
	return stackingQuantity;
}

int Block_Item::getID()
{
	return ID;
}

