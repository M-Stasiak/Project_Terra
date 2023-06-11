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
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities);
	void Use() {};
	unique_ptr<Item> clone() const override {
		return std::make_unique<Block_Item>(*this);
	}

};

class Sword : public Item
{
protected:
	int attackStrength = 10;
	set<Entity*> entitiesToTakeDamage;
public:
	Sword();
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities);
	void Use();
};

class Wooden_Sword : public Sword
{
public:
	Wooden_Sword();
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Wooden_Sword>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};

class Stone_Sword : public Sword
{
public:
	Stone_Sword();
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Stone_Sword>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};

class Gold_Sword : public Sword
{
public:
	Gold_Sword();
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Gold_Sword>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};

