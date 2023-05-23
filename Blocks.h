#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <map>
#include "Block.h"

void prepareTextures(std::map <IDs, sf::Texture*> &arg);
void prepareBlocksMap(std::map<IDs, Block*> &arg1, std::map <IDs, sf::Texture*> &arg2);

class Grass : public Block
{
public:
	Grass(std::map <IDs, sf::Texture*> &arg);
	void test() {};
};

class Dirt : public Block
{
public:
	Dirt(std::map <IDs, sf::Texture*>& arg);
	void test() {};
};

