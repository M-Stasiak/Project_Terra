#include "Block_Item.h"


Block_Item::Block_Item(map<IDs,Texture*>& arg,IDs id,Vector2f pos)
{
	ID = id;
	setTexture(*arg[ID]);
	setTextureRect(sf::IntRect(32, 480, 16, 16));
	setScale(0.5, 0.5);
	setPosition(pos);
}

int Block_Item::getID()
{
	return ID;
}

