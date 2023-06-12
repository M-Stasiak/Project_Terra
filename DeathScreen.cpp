#include "DeathScreen.h"

DeathScreen::DeathScreen(Font& gameFont, RenderWindow& gameWindow)
{
	initTexts(gameFont, gameWindow);
}

void DeathScreen::initTexts(Font& gameFont, RenderWindow& gameWindow)
{
	Vector2f worldPos = gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView());
	back.setSize(Vector2f(gameWindow.getSize().x, gameWindow.getSize().y));
	back.setPosition(worldPos);
	back.setFillColor(Color(0, 0, 0, 100));

	texts[0].setFont(gameFont);
	texts[0].setString("You died! Ugh :(");
	texts[0].setCharacterSize(gameWindow.getSize().x / 26);
	texts[0].setFillColor(Color::Red);
	texts[0].setOutlineColor(Color::Black);
	texts[0].setOutlineThickness(2);
	texts[0].setOrigin(texts[0].getGlobalBounds().width / 2, texts[0].getGlobalBounds().height / 2);

	texts[1].setFont(gameFont);
	texts[1].setString("");
	texts[1].setFillColor(Color::Red);
	texts[1].setCharacterSize(gameWindow.getSize().x / 38);
	texts[1].setOutlineColor(Color::Black);
	texts[1].setOutlineThickness(2);
	texts[1].setOrigin(texts[1].getGlobalBounds().width / 2, texts[1].getGlobalBounds().height / 2);
}

void DeathScreen::update(float elapsed, RenderWindow& gameWindow)
{
	Vector2f worldPos = gameWindow.mapPixelToCoords(Vector2i(0, 0), gameWindow.getView());
	back.setPosition(worldPos);
	texts[0].setPosition(worldPos.x + gameWindow.getSize().x / 4, worldPos.y + gameWindow.getSize().y / 8);
	texts[1].setPosition(worldPos.x + gameWindow.getSize().x / 4, worldPos.y + gameWindow.getSize().y / 4);

	texts[1].setString(to_string(int(elapsed)));
}

void DeathScreen::display(RenderWindow& gameWindow)
{
	gameWindow.draw(back);
	for (int i = 0; i < 2; i++) {
		gameWindow.draw(texts[i]);
	}
}