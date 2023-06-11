#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

enum IDs
{
	AirID,
	GrassID,
	DirtID,
	RockID,
	WoodID,
	PlankID,
	LeavesID,
	CactusID,
	SandID,
	ChestID,
	CraftingTableID,

	WoodenSwordID,
	StoneSwordID,
	GoldenSwordID,
	WoodenPickaxeID,
	StonePickaxeID,
	StickID,
};

class Block : public sf::Sprite
{
protected:
	IDs ID;
	IDs dropID;
	
public:
	Block();
	virtual void test() = 0;
	IDs getDropID();
	
};

class B
{
public:
	IDs ID;
	sf::FloatRect rect;
	int durability;
	B() {}
	B(IDs id, sf::FloatRect r)
	{
		ID = id;
		rect = r;
		switch (ID) {
		
		case(1): {durability = 100; break; }
		case(2): {durability = 100; break; }
		case(3): {durability = 1000; break; }
		case(4): {durability = 500; break; }
		case(5): {durability = 400; break; }
		case(6): {durability = 10; break; }
		case(7): {durability = 50; break; }
		case(8): {durability = 100; break; }
		case(9): { durability = 400; break; }
		case(10): { durability = 400; break; }
		}
	}
};

