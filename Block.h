#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

enum IDs
{
	AirID,
	GrassID,
	DirtID
};

class Block : public sf::Sprite
{
protected:
	IDs ID;

public:
	Block();
	virtual void test() = 0;
};

class B
{
public:
	IDs ID;
	sf::FloatRect rect;
	B()
	{

	}
	B(IDs id, sf::FloatRect r)
	{
		ID = id;
		rect = r;
	}
};

