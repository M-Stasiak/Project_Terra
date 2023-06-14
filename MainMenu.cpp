#include "MainMenu.h"
#include "Animation.h"

void MainMenu::initTextures()
{
	if (!texture.loadFromFile("Textures/mainMenu.png")) { cout << "No texture found" << endl; }
	if (!background_texture.loadFromFile("Textures/mainMenu_background.png")) { cout << "No texture found" << endl; }
	background_texture.setRepeated(true);
	if (!music.openFromFile("Textures/wino.wav")) { cout << "No music found" << endl; }
}

void MainMenu::initSprites(RenderWindow& gameWindow)
{
	animation = new Animation(texture, { {60, 0, 0, 100, 100} });
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 100, 100));
	sprite.setScale(gameWindow.getSize().x / 68, gameWindow.getSize().x / 68);
	int x = gameWindow.getSize().x / 2.5;
	sprite.setPosition(-x, gameWindow.getSize().y / 3);
	background.setTexture(background_texture);
	background.setTextureRect(IntRect(0,0, gameWindow.getSize().x, gameWindow.getSize().y));
	

}

void MainMenu::initTexts(Font& gameFont, RenderWindow& gameWindow)
{
	texts[0].setFont(gameFont);
	texts[0].setString("PROJECT TERRA");
	texts[0].setPosition(gameWindow.getSize().x / 5, gameWindow.getSize().y / 14);
	texts[0].setCharacterSize(gameWindow.getSize().x / 10);
	texts[0].setFillColor(Color::White);
	texts[0].setOutlineColor(Color::Black);
	texts[0].setOutlineThickness(2);

	texts[1].setFont(gameFont);
	texts[1].setString("Play");
	texts[1].setPosition(gameWindow.getSize().x / 1.3, gameWindow.getSize().y / 3);
	texts[1].setFillColor(Color::White);
	texts[1].setCharacterSize(gameWindow.getSize().x / 16);
	texts[1].setOutlineColor(Color::Black);
	texts[1].setOutlineThickness(2);

	texts[2].setFont(gameFont);
	texts[2].setString("Exit");
	texts[2].setPosition(gameWindow.getSize().x / 1.3, gameWindow.getSize().y / 2.2);
	texts[2].setCharacterSize(gameWindow.getSize().x / 16);
	texts[2].setFillColor(Color::White);
	texts[2].setOutlineColor(Color::Black);
	texts[2].setOutlineThickness(2);
}

void MainMenu::update(RenderWindow& gameWindow)
{
	if (Mouse::getPosition(gameWindow).x > texts[1].getGlobalBounds().left && Mouse::getPosition(gameWindow).x < (texts[1].getGlobalBounds().left + texts[1].getGlobalBounds().width) && Mouse::getPosition(gameWindow).y > texts[1].getGlobalBounds().top && Mouse::getPosition(gameWindow).y < texts[1].getGlobalBounds().top + texts[1].getGlobalBounds().height) {
		selectedButton = Play;
		mouseOnButton = play;
	}
	else if (Mouse::getPosition(gameWindow).x > texts[2].getGlobalBounds().left && Mouse::getPosition(gameWindow).x < texts[2].getGlobalBounds().left + texts[2].getGlobalBounds().width && Mouse::getPosition(gameWindow).y > texts[2].getGlobalBounds().top && Mouse::getPosition(gameWindow).y < texts[2].getGlobalBounds().top + texts[2].getGlobalBounds().height) {
		selectedButton = Exit;
		mouseOnButton = exit;
	}
	else { mouseOnButton = none; }
	if (selectedButton == Play) {
		texts[1].setFillColor(Color::Green);
		texts[2].setFillColor(Color::White);
	}
	else if (selectedButton == Exit) {
		texts[2].setFillColor(Color::Green);
		texts[1].setFillColor(Color::White);
	}
}



MainMenu::MainMenu(Font& gameFont, RenderWindow& gameWindow)
{
	initTextures();
	initSprites(gameWindow);
	initTexts(gameFont,gameWindow);
	selectedButton = Play;
}


void MainMenu::display(RenderWindow& gameWindow, Time *elapsed)
{
	gameWindow.draw(background);
	animation->Update(elapsed->asSeconds());
	animation->ApplyToSprite(&sprite);
	gameWindow.draw(sprite);
	update(gameWindow);
	for (int i = 0; i < 3; i++) {
		gameWindow.draw(texts[i]);
	}

}

void MainMenu::selectUp()
{
	selectedButton = Play;
}

void MainMenu::selectDown()
{
	selectedButton = Exit;
}

int MainMenu::returnSelectedButton()
{
	
	return selectedButton;
}

int MainMenu::returnMouseOnButton()
{
	return mouseOnButton;
}

