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
void Game::setGameView()
{
	gameWindow.setView(player.getEntityView());
}



Game::Game()
{
	mainMenu = new MainMenu(gameFont, gameWindow);
	pauseMenu = new PauseMenu(gameFont, gameWindow);
	inventory = new Inventory(gameWindow);
	currentGameMode = gameMode::mainMenu;
	initWindow();
	initFont();
	
}

void Game::dispGame()
{
	
	vector<Entity*> entities;
	entities.push_back(&player);
	RectangleShape rectangle;

	map <IDs, Texture*> Textures;
	map <IDs, Block*> Blocks;
	prepareTextures(Textures);
	prepareBlocksMap(Blocks, Textures);

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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mainMenu->returnSelectedButton()==1) {
					currentGameMode = gameMode::playing;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mainMenu->returnSelectedButton() == 0) {
					gameWindow.close();
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mainMenu->returnSelectedButton() == 1 && mainMenu->returnMouseOnButton()==1) {
					currentGameMode = gameMode::playing;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mainMenu->returnSelectedButton() == 0 && mainMenu->returnMouseOnButton() == 0) {
					gameWindow.close();
				}
				if (gameWindow.pollEvent(gameEvent)) {}
				gameWindow.clear();
				mainMenu->display(gameWindow, &elapsed);
			}

			else if (currentGameMode == gameMode::playing)
			{
				setGameView();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.Up(elapsed.asSeconds());
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.Down(elapsed.asSeconds());
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.Left(elapsed.asSeconds());
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.Right(elapsed.asSeconds());
				if (gameWindow.pollEvent(gameEvent)) {
					if (gameEvent.type == sf::Event::MouseButtonPressed)
						if (gameEvent.mouseButton.button == sf::Mouse::Left)
							player.DestroyBlock(world.world);
					if (gameEvent.type == sf::Event::KeyPressed) {
						if (gameEvent.key.code == Keyboard::Escape) {
					
							currentGameMode = gameMode::pauseMenu;
						}
						else if (gameEvent.key.code == Keyboard::E) {
							
							currentGameMode = gameMode::inventory;
						}
						switch (gameEvent.key.code) {
						case(Keyboard::Num1): {inventory->qInvSelect(1); break; }
						case(Keyboard::Num2): {inventory->qInvSelect(2);  break; }
						case(Keyboard::Num3): { inventory->qInvSelect(3); break; }
						case(Keyboard::Num4): {inventory->qInvSelect(4); break; }
						case(Keyboard::Num5): {inventory->qInvSelect(5); break; }
						case(Keyboard::Num6): { inventory->qInvSelect(6); break; }
						case(Keyboard::Num7): {inventory->qInvSelect(7); break; }
						case(Keyboard::Num8): {inventory->qInvSelect(8); break; }
						case(Keyboard::Num9): {inventory->qInvSelect(9); break; }
						case(Keyboard::Num0): {inventory->qInvSelect(0); break; }

						}
					}
				}
				
				gameWindow.clear();
				//cout << player.getPosition().x << " " << player.getPosition().y << endl;

				for (int i = max((int)player.getPosition().x - 60 * 16, 0); i < min((int)player.getPosition().x + 60 * 16, 16000); i += 16)
				{
					for (int j = max((int)player.getPosition().y - 34 * 16, 0); j < min((int)player.getPosition().y + 34 * 16, 16000); j += 16)
					{
						if (world.world[i / 16][j / 16].ID != IDs::AirID)
						{
							Blocks[world.world[i / 16][j / 16].ID]->setPosition(world.world[i / 16][j / 16].rect.left, world.world[i / 16][j / 16].rect.top);
							gameWindow.draw(*Blocks[world.world[i / 16][j / 16].ID]);
						}
					}
				}
				
				for (auto entity : entities)
				{
					entity->GravityUpdate(elapsed.asSeconds(), 20);
					for (int i = max((int)player.getPosition().x - 60 * 16, 0); i < min((int)player.getPosition().x + 60 * 16, 16000); i += 16)
					{
						for (int j = max((int)player.getPosition().y - 34 * 16, 0); j < min((int)player.getPosition().y + 34 * 16, 16000); j += 16)
						{
							entity->CheckCollisions(&world.world[i / 16][j / 16].rect);
						}
					}
					entity->Update(elapsed.asSeconds());
					entity->Draw(gameWindow);
				}

				rectangle.setFillColor(sf::Color::Transparent);
				rectangle.setOutlineThickness(1);
				rectangle.setOutlineColor(Color::White);
				rectangle.setPosition(player.getGlobalBounds().left, player.getGlobalBounds().top);
				rectangle.setSize(Vector2f(player.getGlobalBounds().width, player.getGlobalBounds().height));
				gameWindow.draw(rectangle);
				
				
				
				inventory->displayQInventory(gameWindow);
				inventory->displayQInventorySelected(gameWindow);
			}
			else if (currentGameMode == gameMode::pauseMenu) {
				gameWindow.clear();
				gameWindow.setView(gameWindow.getDefaultView());

				if (gameWindow.pollEvent(gameEvent)) {
					if (gameEvent.type == sf::Event::KeyPressed) {
						switch (gameEvent.key.code) {
						case (Keyboard::Up): {pauseMenu->selectUp(); break; }
						case (Keyboard::Down): { pauseMenu->selectDown(); break; }
						case (Keyboard::Escape): {currentGameMode = gameMode::playing; break; }
						}
						if (gameEvent.key.code == Keyboard::Enter && pauseMenu->returnSelectedButton() == 1) {
							currentGameMode = gameMode::playing;
						}
						if (gameEvent.key.code == Keyboard::Enter && pauseMenu->returnSelectedButton() == 0) {
							gameWindow.close();
						}
					}
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pauseMenu->returnSelectedButton() == 1 && pauseMenu->returnMouseOnButton() == 1) {
					currentGameMode = gameMode::playing;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pauseMenu->returnSelectedButton() == 0 && pauseMenu->returnMouseOnButton() == 0) {
					gameWindow.close();
				}
				
				
				pauseMenu->display(gameWindow, &elapsed);
			}
			else if (currentGameMode == gameMode::inventory) {
		
				setGameView();
				gameWindow.clear();
				for (int i = max((int)player.getPosition().x - 60 * 16, 0); i < min((int)player.getPosition().x + 60 * 16, 16000); i += 16)
				{
					for (int j = max((int)player.getPosition().y - 34 * 16, 0); j < min((int)player.getPosition().y + 34 * 16, 16000); j += 16)
					{
						if (world.world[i / 16][j / 16].ID != IDs::AirID)
						{
							Blocks[world.world[i / 16][j / 16].ID]->setPosition(world.world[i / 16][j / 16].rect.left, world.world[i / 16][j / 16].rect.top);
							gameWindow.draw(*Blocks[world.world[i / 16][j / 16].ID]);
						}
					}
				}

				for (auto entity : entities)
				{
					entity->GravityUpdate(elapsed.asSeconds(), 20);
					for (int i = max((int)player.getPosition().x - 60 * 16, 0); i < min((int)player.getPosition().x + 60 * 16, 16000); i += 16)
					{
						for (int j = max((int)player.getPosition().y - 34 * 16, 0); j < min((int)player.getPosition().y + 34 * 16, 16000); j += 16)
						{
							entity->CheckCollisions(&world.world[i / 16][j / 16].rect);
						}
					}
					entity->Update(elapsed.asSeconds());
					entity->Draw(gameWindow);
				}
				inventory->displayInventory(gameWindow);
				inventory->displayInventorySelected(gameWindow);
				if (gameWindow.pollEvent(gameEvent)) {
					if (gameEvent.type == sf::Event::KeyPressed) {
						if (gameEvent.key.code == Keyboard::E) {
							currentGameMode = gameMode::playing;
						}
						if (gameEvent.key.code == Keyboard::Escape) {
							currentGameMode = gameMode::pauseMenu;
						}
					}
				}
				
				
			}
			
			gameWindow.display();
		}
	
}



