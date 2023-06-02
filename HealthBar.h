#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class HealthBar
{
private:
	int value, max;
	Texture backgroundBarTexture;
	RectangleShape bar;
	Sprite backgroundBar;

public:
	HealthBar();
	HealthBar(int _value, int _max);
	void setHealthBar(int _value, int _max);

	void Draw(RenderWindow& gameWindow, int _value, FloatRect entityGlobalBounds);
};

