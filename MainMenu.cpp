#include "MainMenu.h"
#include "Animation.h"

void MainMenu::initTextures()
{
	if (!texture.loadFromFile("Textures/mainMenu.png")) { cout << "No texture found" << endl; }
}

void MainMenu::initSprites(RenderWindow& gameWindow)
{
	animation = new Animation(texture, { {60, 0, 0, 100, 100} });
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 100, 100));
	sprite.setScale(20, 20);
	sprite.setPosition(gameWindow.getView().getCenter().x-1000, gameWindow.getView().getCenter().y-250);

}

void MainMenu::initTexts(Font& gameFont, RenderWindow& gameWindow)
{
	texts[0].setFont(gameFont);
	texts[0].setString("PROJECT TERRA");
	texts[0].setPosition(gameWindow.getView().getCenter().x, gameWindow.getView().getCenter().y-470);
	texts[0].setCharacterSize(130);
	texts[0].setFillColor(Color::Green);
	texts[0].setOutlineColor(Color::Black);
	texts[0].setOutlineThickness(2);

	texts[1].setFont(gameFont);
	texts[1].setString("Play");
	texts[1].setPosition(gameWindow.getView().getCenter().x +770, gameWindow.getView().getCenter().y-200);
	texts[1].setFillColor(Color::Green);
	texts[1].setCharacterSize(80);
	texts[1].setOutlineColor(Color::Black);
	texts[1].setOutlineThickness(2);

	texts[2].setFont(gameFont);
	texts[2].setString("Exit");
	texts[2].setPosition(gameWindow.getView().getCenter().x +770, gameWindow.getView().getCenter().y-100);
	texts[2].setCharacterSize(80);
	texts[2].setFillColor(Color::Green);
	texts[2].setOutlineColor(Color::Black);
	texts[2].setOutlineThickness(2);
}



MainMenu::MainMenu(Font& gameFont, RenderWindow& gameWindow)
{
	initTextures();
	initSprites(gameWindow);
	initTexts(gameFont,gameWindow);

}

MainMenu::~MainMenu()
{
}

void MainMenu::display(RenderWindow& gameWindow, Time *elapsed)
{
	animation->Update(elapsed->asSeconds());
	animation->ApplyToSprite(&sprite);
	gameWindow.draw(sprite);
	for (int i = 0; i < 3; i++) {
		gameWindow.draw(texts[i]);
	}

}
