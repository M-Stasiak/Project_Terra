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
	StickID
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
	B() {}
	B(IDs id, sf::FloatRect r)
	{
		ID = id;
		rect = r;
	}

};

