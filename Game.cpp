#include "Game.h"
#include "Zombie.h"

void Game::initFont()
{
	if (!gameFont.loadFromFile("Fonts/font.ttf")) { cout << "No font file found"; }


}

void Game::initWindow()
{
	gameWindow.create(VideoMode::getDesktopMode(), "Project Terra", Style::Fullscreen);
	gameWindow.setFramerateLimit(60);
	gameWindow.setVerticalSyncEnabled(true);
}

void Game::setGameView()
{
	gameWindow.setView(player.getEntityView());
}



Game::Game()
{
	initWindow();
	initFont();
	mainMenu = new MainMenu(gameFont, gameWindow);
	pauseMenu = new PauseMenu(gameFont, gameWindow);
	currentGameMode = gameMode::mainMenu;
	
}

void Game::dispGame()
{
	Zombie zombie;
	vector<Entity*> entities;
	entities.push_back(&player);
	entities.push_back(&zombie);
	RectangleShape rectangle;
	RectangleShape rectangle1;

	map <IDs, Texture*> Textures;
	map <IDs, Block*> Blocks;
	prepareTextures(Textures);
	prepareBlocksMap(Blocks, Textures);
	inventory = new Inventory(gameWindow, gameFont,Textures,Blocks);
	Background background;

	Weapon miecz;
	miecz.setPosition(100, 100);

	GameWorld world;
	//world.items_on_ground.emplace_back(&miecz);
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.Up(0.02);
				//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.Down(0.02);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.Left(0.02);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.Right(0.02);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (inventory->inv_vector[inventory->getQInventorySelected()].first != nullptr and inventory->inv_vector[inventory->getQInventorySelected()].first->getItemType() == item_type::tool)
					{
						inventory->inv_vector[inventory->getQInventorySelected()].first->Use();
					}
					else
					{
						player.DestroyBlock(world.world, gameWindow);
						if (player.isBlockDestroyed() == true) {
							world.dropItem(Blocks[player.getDestroyedBlockID()]->getDropID(), Textures, Blocks, player.getDestroyedBlockPosition());
						}
					}
				}
				if (gameWindow.pollEvent(gameEvent)) {

					if (gameEvent.type == sf::Event::KeyPressed) {
						if (gameEvent.key.code == Keyboard::Escape) {
					
							currentGameMode = gameMode::pauseMenu;
						}
						else if (gameEvent.key.code == Keyboard::E) {
							
							currentGameMode = gameMode::inventory;
						}
						switch (gameEvent.key.code) {
						case(Keyboard::Num1): {inventory->qInvSelect(0); break; }
						case(Keyboard::Num2): {inventory->qInvSelect(1);  break; }
						case(Keyboard::Num3): { inventory->qInvSelect(2); break; }
						case(Keyboard::Num4): {inventory->qInvSelect(3); break; }
						case(Keyboard::Num5): {inventory->qInvSelect(4); break; }
						case(Keyboard::Num6): { inventory->qInvSelect(5); break; }
						case(Keyboard::Num7): {inventory->qInvSelect(6); break; }
						case(Keyboard::Num8): {inventory->qInvSelect(7); break; }
						case(Keyboard::Num9): {inventory->qInvSelect(8); break; }
						case(Keyboard::Num0): {inventory->qInvSelect(9); break; }

						}
					}
					if (gameEvent.type == sf::Event::MouseButtonPressed) {
						if (gameEvent.key.code == Mouse::Right) {
							if (inventory->inv_vector[inventory->getQInventorySelected()].first != nullptr)
							{
								if (inventory->inv_vector[inventory->getQInventorySelected()].first->getItemType() == item_type::block)
								{
									player.EmplaceBlock(world.world, gameWindow, inventory->getQInventorySelectedID());
									if (player.isBlockPlaced() == true) {
										inventory->inv_vector[inventory->getQInventorySelected()].second--;
									}
								}
							}
						}
					}
				}
				
				gameWindow.clear();
				background.Render(gameWindow);

				for (int i = max((int)player.getPosition().x - renderWidth * 16, 0); i < min((int)player.getPosition().x + renderWidth * 16, 16000); i += 16)
				{
					for (int j = max((int)player.getPosition().y - renderHeight * 16, 0); j < min((int)player.getPosition().y + renderHeight * 16, 16000); j += 16)
					{
						if (world.world[i / 16][j / 16].ID != IDs::AirID)
						{
							Blocks[world.world[i / 16][j / 16].ID]->setPosition(world.world[i / 16][j / 16].rect.left, world.world[i / 16][j / 16].rect.top);
							gameWindow.draw(*Blocks[world.world[i / 16][j / 16].ID]);
						}
					}
				}
				zombie.UpdateAI(elapsed.asSeconds(), player, world.world);
				for (auto entity : entities)
				{
					entity->GravityUpdate(0.02, 20);
					for (int i = max((int)entity->getPosition().x - collisionsCheckWidth * 16, 0); i < min((int)entity->getPosition().x + collisionsCheckWidth * 16, 16000); i += 16)
					{
						for (int j = max((int)entity->getPosition().y - collisionsCheckHeight * 16, 0); j < min((int)entity->getPosition().y + collisionsCheckHeight * 16, 16000); j += 16)
						{
							entity->CheckCollisions(&world.world[i / 16][j / 16].rect);
						}
					}
					entity->Update(elapsed.asSeconds());
					entity->Draw(gameWindow);
				}
				if (inventory->inv_vector[inventory->getQInventorySelected()].first != nullptr and inventory->inv_vector[inventory->getQInventorySelected()].first->getItemType() == item_type::tool)
				{
					inventory->inv_vector[inventory->getQInventorySelected()].first->Update(elapsed.asSeconds(), player, entities);
					gameWindow.draw(*inventory->inv_vector[inventory->getQInventorySelected()].first);
				}
				
				for (auto& item : world.items_on_ground)
				{
					if (item != nullptr and (item->getPosition().x > player.getPosition().x - renderWidth * 16 and item->getPosition().x < player.getPosition().x + renderWidth * 16 and item->getPosition().y > player.getPosition().y - renderHeight * 16 and item->getPosition().y < player.getPosition().y + renderHeight * 16))
					{
						player.updatePickUpRange();
						if (item->getGlobalBounds().intersects(player.getPlayerPickUpRange()) && inventory->isInventoryFull(item->getID()) == false) {
							item->goToPlayer(player.getPosition());
							if (item->getGlobalBounds().intersects(player.getGlobalBounds())) {
								auto it = find_if(inventory->inv_vector.begin(), inventory->inv_vector.end(), [&item](auto& el) {return el.first != nullptr && item->getID() == el.first->getID() && el.second < item->getStackingQuantity(); });
								if (it != inventory->inv_vector.end()) {
									it->second++;
									auto ite = find(world.items_on_ground.begin(), world.items_on_ground.end(), item);
									world.items_on_ground.erase(ite);
								}
								else {
									auto ite1 = find_if(inventory->inv_vector.begin(), inventory->inv_vector.end(), [](auto& el) {return el.first == nullptr; });
									ite1->first.swap(item);
									ite1->second++;
									if (item == nullptr) {
										auto ite = find(world.items_on_ground.begin(), world.items_on_ground.end(), item);
										world.items_on_ground.erase(ite);
									}

								}
							}
								
						
						}
						else {
							item->GravityUpdate(elapsed.asSeconds(), 5);
							for (int i = max((int)item->getPosition().x - collisionsCheckWidth * 16, 0); i < min((int)item->getPosition().x + collisionsCheckWidth * 16, 16000); i += 16)
							{
								for (int j = max((int)item->getPosition().y - collisionsCheckHeight * 16, 0); j < min((int)item->getPosition().y + collisionsCheckHeight * 16, 16000); j += 16)
								{
									item->CheckCollisions(&world.world[i / 16][j / 16].rect);
								}
							}
						}
					}
				}
				world.drawItemsOnGround(gameWindow, player.getPosition(), renderWidth, renderHeight);

				rectangle.setFillColor(sf::Color::Transparent);
				rectangle.setOutlineThickness(1);
				rectangle.setOutlineColor(Color::White);
				rectangle.setPosition(player.getGlobalBounds().left, player.getGlobalBounds().top);
				rectangle.setSize(Vector2f(player.getGlobalBounds().width, player.getGlobalBounds().height));
				//gameWindow.draw(rectangle);
				
				
				
				player.updateReach();
				
				inventory->displayQInventory(gameWindow);
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
				background.Render(gameWindow);
				for (int i = max((int)player.getPosition().x - renderWidth * 16, 0); i < min((int)player.getPosition().x + renderWidth * 16, 16000); i += 16)
				{
					for (int j = max((int)player.getPosition().y - renderHeight * 16, 0); j < min((int)player.getPosition().y + renderHeight * 16, 16000); j += 16)
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
					entity->GravityUpdate(0.02, 20);
					for (int i = max((int)entity->getPosition().x - collisionsCheckWidth * 16, 0); i < min((int)entity->getPosition().x + collisionsCheckWidth * 16, 16000); i += 16)
					{
						for (int j = max((int)entity->getPosition().y - collisionsCheckHeight * 16, 0); j < min((int)entity->getPosition().y + collisionsCheckHeight * 16, 16000); j += 16)
						{
							entity->CheckCollisions(&world.world[i / 16][j / 16].rect);
						}
					}
					entity->Update(elapsed.asSeconds());
					entity->Draw(gameWindow);
				}
				inventory->displayInventory(gameWindow,Textures);
				if (gameWindow.pollEvent(gameEvent)) {
					if (gameEvent.type == sf::Event::KeyPressed) {
						if (gameEvent.key.code == Keyboard::E) {
							currentGameMode = gameMode::playing;
						}
						if (gameEvent.key.code == Keyboard::Escape) {
							currentGameMode = gameMode::pauseMenu;
						}
					}
					else if (gameEvent.type == Event::MouseButtonPressed) {
						if (gameEvent.key.code == Mouse::Left) {
							if (inventory->mouseItem.first == nullptr || inventory->inv_vector[inventory->getInventorySelected()].first == nullptr) {
								inventory->mouseItem.swap(inventory->inv_vector[inventory->getInventorySelected()]);
							}
							else if (inventory->mouseItem.first != nullptr && inventory->inv_vector[inventory->getInventorySelected()].first != nullptr) {

								if (inventory->mouseItem.first->getID() != inventory->inv_vector[inventory->getInventorySelected()].first->getID()) {
									inventory->mouseItem.swap(inventory->inv_vector[inventory->getInventorySelected()]);
								}
								else if (inventory->mouseItem.first->getID() == inventory->inv_vector[inventory->getInventorySelected()].first->getID()) {
									if (inventory->mouseItem.second + inventory->inv_vector[inventory->getInventorySelected()].second < inventory->mouseItem.first->getStackingQuantity()) {
										inventory->inv_vector[inventory->getInventorySelected()].second += inventory->mouseItem.second;
										inventory->mouseItem.second -= inventory->mouseItem.second;
									}
									else {
										int difference = inventory->mouseItem.first->getStackingQuantity() - inventory->inv_vector[inventory->getInventorySelected()].second;
										if (difference > 0) {
											inventory->inv_vector[inventory->getInventorySelected()].second += difference;
											inventory->mouseItem.second -= difference;
										}
										else { inventory->mouseItem.swap(inventory->inv_vector[inventory->getInventorySelected()]); }

									}
								}
							}
							if (inventory->isMouseOnCrafitng() == true) {
								inventory->setCraftSelected(inventory->getMouseOnCraft());
							}
						}
					}
				}
				
				
			}
			
			gameWindow.display();
		}
	
}



