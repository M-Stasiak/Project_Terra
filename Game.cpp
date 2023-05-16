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
	Player player;
	vector<Entity*> entities;
	entities.push_back(&player);
	Clock clock;
	while (gameWindow.isOpen()) {

		Time elapsed = clock.restart();

		if (gameWindow.pollEvent(gameEvent)) {
			if (gameEvent.type == sf::Event::KeyPressed)
			{
				if (gameEvent.key.code == sf::Keyboard::Escape)
					gameWindow.close();
				if (gameEvent.key.code == sf::Keyboard::Enter)
					currentGameMode = gameMode::playing;
			}
		}
		if (currentGameMode == gameMode::mainMenu) {
			mainMenu->display(gameWindow, &elapsed);
		}

		if (currentGameMode == gameMode::playing)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.Up(elapsed.asSeconds());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.Down(elapsed.asSeconds());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.Left(elapsed.asSeconds());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.Right(elapsed.asSeconds());

			gameWindow.clear(sf::Color::Black);

			for (auto i : entities)
			{
				i->Update(elapsed.asSeconds());
				i->Draw(gameWindow);
			}

		}


		gameWindow.display();
	}
}

