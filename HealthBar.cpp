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

void HealthBar::setPlayerHealthBar(int _value, int _max)
{
	value = _value;
	max = _max;
	heartTexture.loadFromFile("Textures/PixelHeart.png");
	font.loadFromFile("Fonts/font.ttf");
	heart.setTexture(heartTexture);
	heartTextureRect[HeartID::Full] = { 0, 0, 16, 16 };
	heartTextureRect[HeartID::Half] = { 16, 0, 16, 16 };
	heartTextureRect[HeartID::Empty] = { 32, 0, 16, 16 };

	text.setFont(font);
	text.setCharacterSize(10);
	text.setFillColor(Color::White);
	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(1);
}

void HealthBar::Draw(RenderWindow& gameWindow, int _value, FloatRect entityGlobalBounds)
{
	value = _value;
	if (value < 0) { value = 0; }
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

void HealthBar::Draw(RenderWindow& gameWindow, int _value)
{
	value = _value;
	if (value < 0) { value = 0; }
	float percentage = float(value) / max;
	int n = max / 10;
	for (int i = 1; i <= n; i++)
	{
		if (value >= i * 10) heart.setTextureRect(heartTextureRect[HeartID::Full]);
		else if (value < i * 10 and value > (i-1) * 10)  heart.setTextureRect(heartTextureRect[HeartID::Half]);
		else  heart.setTextureRect(heartTextureRect[HeartID::Empty]);

		heart.setPosition(gameWindow.mapPixelToCoords(Vector2i(gameWindow.getSize().x - 30 * heart.getGlobalBounds().width, 0), gameWindow.getView()).x + i * heart.getGlobalBounds().width, gameWindow.mapPixelToCoords(Vector2i(0, 10), gameWindow.getView()).y);
		gameWindow.draw(heart);
	}
	text.setString(to_string(value) + " / " + to_string(max));
	text.setPosition(heart.getGlobalBounds().left + heart.getGlobalBounds().width + 10, heart.getPosition().y);
	gameWindow.draw(text);

}