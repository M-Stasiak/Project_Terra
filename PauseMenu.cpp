#include "PauseMenu.h"

void PauseMenu::initTexts(Font& gameFont, RenderWindow& gameWindow)
{
	texts[0].setFont(gameFont);
	texts[0].setString("PAUSE MENU");
	texts[0].setPosition(gameWindow.getView().getCenter().x-80, gameWindow.getView().getCenter().y - 470);
	texts[0].setCharacterSize(130);
	texts[0].setFillColor(Color::White);
	texts[0].setOutlineColor(Color::Black);
	texts[0].setOutlineThickness(2);

	texts[1].setFont(gameFont);
	texts[1].setString("Continue");
	texts[1].setPosition(gameWindow.getView().getCenter().x+105, gameWindow.getView().getCenter().y - 200);
	texts[1].setFillColor(Color::White);
	texts[1].setCharacterSize(80);
	texts[1].setOutlineColor(Color::Black);
	texts[1].setOutlineThickness(2);

	texts[2].setFont(gameFont);
	texts[2].setString("Exit Game");
	texts[2].setPosition(gameWindow.getView().getCenter().x+90, gameWindow.getView().getCenter().y - 100);
	texts[2].setCharacterSize(80);
	texts[2].setFillColor(Color::White);
	texts[2].setOutlineColor(Color::Black);
	texts[2].setOutlineThickness(2);
}

void PauseMenu::update()
{
	if (selectedButton == Continue) {
		texts[1].setFillColor(Color::Green);
		texts[2].setFillColor(Color::White);
	}
	else if (selectedButton == Exit) {
		texts[2].setFillColor(Color::Green);
		texts[1].setFillColor(Color::White);
	}
}

PauseMenu::PauseMenu(Font& gameFont, RenderWindow& gameWindow)
{
	initTexts(gameFont, gameWindow);
	selectedButton = Continue;
	
}

void PauseMenu::display(RenderWindow& gameWindow, Time* elapsed)
{
	update();
	for (int i = 0; i < 3; i++) {
		gameWindow.draw(texts[i]);
	}
	
}

void PauseMenu::selectUp()
{
	selectedButton = Continue;
}

void PauseMenu::selectDown()
{
	selectedButton = Exit;
}

bool PauseMenu::returnContinueSelected()
{
	if (selectedButton == Continue) {
		return true;
	}
	return false;
}

bool PauseMenu::returnExitSelected()
{
	if (selectedButton == Exit) {
		return true;
	}
	return false;
}
