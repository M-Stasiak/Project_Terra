#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

class DeathScreen
{
private:
	Text texts[2];
	RectangleShape back;

public:
	DeathScreen(Font& gameFont, RenderWindow& gameWindow);
	void initTexts(Font& gameFont, RenderWindow& gameWindow);
	void update(float elapsed, RenderWindow& gameWindow);
	void display(RenderWindow& gameWindow);
};

