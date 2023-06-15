#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Item.h"
#include <set>

using namespace sf;
using namespace std;

void prepareItemsMap(std::map<IDs, Item*>& arg1, std::map <IDs, sf::Texture*>& arg2);
void prepareItemsTextures(std::map <IDs, sf::Texture*>& arg);

class Block_Item : public Item
{
public:
	Block_Item(map <IDs, sf::Texture*>& arg1, map <IDs, Block*>& arg2, IDs id, Vector2f pos);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		return std::make_unique<Block_Item>(*this);
	}

};

class Material_Item : public Item
{

public:
	Material_Item(IDs id, map <IDs, sf::Texture*>& arg1, map <IDs, Item*>& arg3, Vector2f pos);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		return std::make_unique<Material_Item>(*this);
	}

};
class Tool_Item : public Item
{
private:
	int attackStrength = 10;
	set<Entity*> entitiesToTakeDamage;
public:
	Tool_Item(IDs id, map <IDs, sf::Texture*>& arg1, map <IDs, Item*>& arg3, Vector2f pos);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities);
	void Use();
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Tool_Item>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};





//class Sword : public Item
//{
//protected:
//	int attackStrength = 10;
//	set<Entity*> entitiesToTakeDamage;
//public:
//	Sword();
//	void nothing() {};
//	void Update(float elapsed, Entity& entity, vector<Entity*>& entities);
//	void Use();
//};

class Wooden_Sword : public Item
{
public:
	Wooden_Sword(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Wooden_Sword>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};

class Stone_Sword : public Item
{
public:
	Stone_Sword(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Stone_Sword>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};
class Wooden_Pickaxe : public Item
{
public:
	Wooden_Pickaxe(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Wooden_Pickaxe>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};
class Stone_Pickaxe : public Item
{
public:
	Stone_Pickaxe(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Stone_Pickaxe>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};


class Stick : public Item
{
public:
	Stick(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		return std::make_unique<Stick>(*this);
	}

};

class Apple : public Item
{
public:
	Apple(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		return std::make_unique<Apple>(*this);
	}

};

class IronIngot : public Item {

public:
	IronIngot(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		return std::make_unique<IronIngot>(*this);
	}
};
class GoldIngot : public Item {

public:
	GoldIngot(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		return std::make_unique<GoldIngot>(*this);
	}
};
class EmeraldItem : public Item {

public:
	EmeraldItem(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		return std::make_unique<EmeraldItem>(*this);
	}
};
class DiamondItem : public Item {

public:
	DiamondItem(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		return std::make_unique<DiamondItem>(*this);
	}
};


class Golden_Pickaxe : public Item
{
public:
	Golden_Pickaxe(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Golden_Pickaxe>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};
class Diamond_Pickaxe : public Item
{
public:
	Diamond_Pickaxe(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Diamond_Pickaxe>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};
class Emerald_Pickaxe : public Item
{
public:
	Emerald_Pickaxe(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Emerald_Pickaxe>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};
class Iron_Pickaxe : public Item
{
public:
	Iron_Pickaxe(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Iron_Pickaxe>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};

class Iron_Sword : public Item
{
public:
	Iron_Sword(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Iron_Sword>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};
class Golden_Sword : public Item
{
public:
	Golden_Sword(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Golden_Sword>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};
class Diamond_Sword : public Item
{
public:
	Diamond_Sword(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Diamond_Sword>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};
class Emerald_Sword : public Item
{
public:
 Emerald_Sword(std::map<IDs, sf::Texture*>& arg);
	void nothing() {};
	void Update(float elapsed, Entity& entity, vector<Entity*>& entities) {};
	void Use() {};
	unique_ptr<Item> clone() const override {
		unique_ptr<Item> result = make_unique<Emerald_Sword>(*this);
		result->setOrigin(result->getSpecialOrigin());
		result->setScale(1, 1);
		return result;
	}

};