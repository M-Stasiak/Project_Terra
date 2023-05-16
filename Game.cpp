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

	RectangleShape block(Vector2f(100, 100));
	block.setPosition(100, 100);
	block.setFillColor(sf::Color::Red);
	RectangleShape block2(Vector2f(100, 100));
	block2.setPosition(400, 100);
	block2.setFillColor(sf::Color::Red);

	vector<RectangleShape*> blocks;
	blocks.push_back(&block);
	blocks.push_back(&block2);

	sf::Texture t1;
	t1.loadFromFile("Textures/tileset.png");
	Block block1(t1, { 15, 15, 18, 18 }, sf::Vector2f(0, 0));
	GameWorld world;
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
			gameWindow.draw(block);
			gameWindow.draw(block2);

			/*for (auto i : world.world)
				for (auto j : i)
				{
					gameWindow.draw(*j);

				}*/
			/*for (auto i : world.world)
				gameWindow.draw(*i);*/
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < 100; j++)
				{
					if (world.world[i][j] == IDs::Grass)
					{
						block1.setPosition(i * 20, j * 20);
						gameWindow.draw(block1);
					}
				}
			}

			for (auto i : entities)
			{
				for (auto j : blocks)
				{
					i->CheckCollisions(j);
				}
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

