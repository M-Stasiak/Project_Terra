#include "HealthBar.h"

HealthBar::HealthBar() {}

HealthBar::HealthBar(int _value, int _max)
{
	backgroundBarTexture.loadFromFile("Textures/bars.png");
	backgroundBar.setTexture(backgroundBarTexture);
	backgroundBar.setTextureRect(IntRect(0, 4, 48, 7));
	backgroundBar.setScale(0.5, 0.75);
	bar.setSize(Vector2f(backgroundBar.getGlobalBounds().width - 2, backgroundBar.getGlobalBounds().height - 2));
	value = _value;
	max = _max;
}

void HealthBar::setHealthBar(int _value, int _max)
{
	backgroundBarTexture.loadFromFile("Textures/bars.png");
	backgroundBar.setTexture(backgroundBarTexture);
	backgroundBar.setTextureRect(IntRect(0, 4, 48, 7));
	backgroundBar.setScale(0.5, 0.75);
	bar.setSize(Vector2f(backgroundBar.getGlobalBounds().width - 2, backgroundBar.getGlobalBounds().height - 2));
	value = _value;
	max = _max;
}

void HealthBar::Draw(RenderWindow& gameWindow, int _value, FloatRect entityGlobalBounds)
{
	value = _value;
	float percentage = float(value) / max;
	backgroundBar.setPosition(entityGlobalBounds.left - (backgroundBar.getGlobalBounds().width - entityGlobalBounds.width) / 2, entityGlobalBounds.top + entityGlobalBounds.height + 5);
	bar.setPosition(backgroundBar.getPosition().x + 1, backgroundBar.getPosition().y + 1);
	bar.setScale(percentage, 1);
	if (percentage >= 0.77)  bar.setFillColor(Color::Green);
	else if (percentage >= 0.33 and percentage < 0.77)  bar.setFillColor(Color::Yellow);
	else bar.setFillColor(Color::Red);
	gameWindow.draw(backgroundBar);
	gameWindow.draw(bar);
}