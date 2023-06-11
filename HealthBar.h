#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

enum HeartID
{
	Full,
	Half,
	Empty
};

class HealthBar
{
private:
	int value, max;

	Texture backgroundBarTexture;
	RectangleShape bar;
	Sprite backgroundBar;

	Texture heartTexture;
	map<HeartID, IntRect> heartTextureRect;
	Sprite heart;
	Font font;
	Text text;

public:
	HealthBar();
	HealthBar(int _value, int _max);
	void setHealthBar(int _value, int _max);
	void setPlayerHealthBar(int _value, int _max);

	void Draw(RenderWindow& gameWindow, int _value, FloatRect entityGlobalBounds);
	void Draw(RenderWindow& gameWindow, int _value);
};

