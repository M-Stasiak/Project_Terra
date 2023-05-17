#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

enum IDs
{
	Air = 0,
	Grass = 1
};

class Block : public sf::Sprite
{
private:
	IDs ID;

public:
	Block();
	Block(sf::Texture& _texture, std::vector<int> options, sf::Vector2f pos);
	void setBlock(sf::Texture& _texture, std::vector<int> options);
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

