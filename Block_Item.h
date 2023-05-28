#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Item.h"

using namespace sf;
using namespace std;



class Block_Item : public Item
{
private:
	item_type type = item_type::block;
	IDs ID;

public:
	Block_Item(map <IDs, sf::Texture*>& arg1, map <IDs, Block*>& arg2, IDs id, Vector2f pos);
	int getID();
	void nothing() {};
};
