#include "Game.h"

void Game::initFont()
{
	if (!gameFont.loadFromFile("Fonts/font.ttf")) { cout << "No font file found"; }


}

void Game::initWindow()
{
	gameWindow.create(VideoMode::getDesktopMode(), "Project Terra", Style::Fullscreen);
	gameWindow.setFramerateLimit(60);
}

Game::Game()
{
	mainMenu = new MainMenu(gameFont, gameWindow);
	currentGameMode = gameMode::mainMenu;
	initWindow();
	initFont();
}

void Game::dispGame()
{
	while (gameWindow.isOpen()) {
		if (gameWindow.pollEvent(gameEvent)) {
			if (currentGameMode == gameMode::mainMenu) {
					mainMenu->display(gameWindow);
					gameWindow.display();

			}
			if (gameEvent.type == sf::Event::KeyPressed)
				gameWindow.close();
		}
	}
}

