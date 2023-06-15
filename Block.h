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
	ClayID,
	BricksID,
	HayID,
	DiamondID,
	IronID,
	EmeraldID,
	GoldID,

	WoodenSwordID,
	StoneSwordID,
	GoldenSwordID,
	WoodenPickaxeID,
	StonePickaxeID,

	StickID,
	AppleID
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
		
		case(IDs::GrassID): {durability = 100; break; }
		case(IDs::DirtID): {durability = 100; break; }
		case(IDs::RockID): {durability = 1000; break; }
		case(IDs::WoodID): {durability = 500; break; }
		case(IDs::PlankID): {durability = 400; break; }
		case(IDs::LeavesID): {durability = 10; break; }
		case(IDs::CactusID): {durability = 50; break; }
		case(IDs::SandID): {durability = 100; break; }
		case(IDs::ChestID): { durability = 400; break; }
		case(IDs::CraftingTableID): { durability = 400; break; }
		case(IDs::ClayID): { durability = 100; break; }
		case(IDs::BricksID): { durability = 1000; break; }
		case(IDs::HayID): { durability = 100; break; }
		case(IDs::DiamondID): { durability = 4000; break; }
		case(IDs::IronID): { durability = 2000; break; }
		case(IDs::EmeraldID): { durability = 3000; break; }
		case(IDs::GoldID): { durability = 3000; break; }
		}
	}
};

