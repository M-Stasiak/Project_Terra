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
	pauseMenu = new PauseMenu(gameFont, gameWindow);
	currentGameMode = gameMode::mainMenu;
	initWindow();
	initFont();
}

void Game::dispGame()
{
	Player player;
	vector<Entity*> entities;
	entities.push_back(&player);
	Clock clock;
	while (gameWindow.isOpen()) {

		Time elapsed = clock.restart();

		
		if (currentGameMode == gameMode::mainMenu) {
			
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					mainMenu->selectUp();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					mainMenu->selectDown();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mainMenu->returnPlaySelected()) {
					currentGameMode = gameMode::playing;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mainMenu->returnExitSelected()) {
					gameWindow.close();
				}
				
			mainMenu->display(gameWindow, &elapsed);
		}

		if (currentGameMode == gameMode::playing)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.Up(elapsed.asSeconds());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.Down(elapsed.asSeconds());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.Left(elapsed.asSeconds());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.Right(elapsed.asSeconds());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				currentGameMode = gameMode::pauseMenu;
			}

			gameWindow.clear(sf::Color::Black);

			for (auto i : entities)
			{
				i->Update(elapsed.asSeconds());
				i->Draw(gameWindow);
			}

		}
		if (currentGameMode == gameMode::pauseMenu) {
			gameWindow.clear();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				pauseMenu->selectUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				pauseMenu->selectDown();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pauseMenu->returnContinueSelected()) {
				currentGameMode = gameMode::playing;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pauseMenu->returnExitSelected()) {
				gameWindow.close();
			}
			

			pauseMenu->display(gameWindow, &elapsed);
		}


		gameWindow.display();
	}
}

