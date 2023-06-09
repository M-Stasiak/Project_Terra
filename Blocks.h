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

class Rock : public Block
{
public:
	Rock(std::map <IDs, sf::Texture*>& arg);
	void test() {};
};

class Wood : public Block
{
public:
	Wood(std::map <IDs, sf::Texture*>& arg);
	void test() {};
};

class Plank : public Block
{
public:
	Plank(std::map <IDs, sf::Texture*>& arg);
	void test() {};
};

class Leaves : public Block
{
public:
	Leaves(std::map <IDs, sf::Texture*>& arg);
	void test() {};
};

class Cactus : public Block
{
public:
	Cactus(std::map <IDs, sf::Texture*>& arg);
	void test() {};
};

class Sand : public Block
{
public:
	Sand(std::map <IDs, sf::Texture*>& arg);
	void test() {};
};

class Chest : public Block
{
public:
	Chest(std::map <IDs, sf::Texture*>& arg);
	void test() {};
};

class CraftingTable : public Block
{
public:
	CraftingTable(std::map <IDs, sf::Texture*>& arg);
	void test() {}
};

