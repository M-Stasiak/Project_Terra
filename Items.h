#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Item.h"
#include <set>

using namespace sf;
using namespace std;

class Block_Item : public Item
{
public:
	Block_Item(map <IDs, sf::Texture*>& arg1, map <IDs, Block*>& arg2, IDs id, Vector2f pos);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
};

class Weapon : public Item
{
private:
	set<Entity*> entitiesToTakeDamage;
public:
	Weapon();
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities);
	void Use();
};
