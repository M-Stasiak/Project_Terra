#include "Block_Item.h"


Block_Item::Block_Item(map<IDs,Texture*>& arg1, map <IDs, Block*>& arg2, IDs id,Vector2f pos)
{
	ID = id;
	setTexture(*arg1[ID]);
	setTextureRect(arg2[ID]->getTextureRect());
	setScale(0.5, 0.5);
	setPosition(pos);
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

