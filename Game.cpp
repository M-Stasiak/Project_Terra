#include "Game.h"
#include "Zombie.h"

void Game::initFont()
{
	if (!gameFont.loadFromFile("Fonts/font.ttf")) { cout << "No font file found"; }


}

void Game::initWindow()
{
	gameWindow.create(VideoMode::getDesktopMode(), "Project Terra", Style::Default);
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
	deathScreen = new DeathScreen(gameFont, gameWindow);
	currentGameMode = gameMode::mainMenu;
	
}

void Game::dispGame()
{
	vector<Entity*> entities;
	entities.push_back(&player);
	entities.push_back(new Zombie);
	RectangleShape rectangle;
	RectangleShape rectangle1;

	map <IDs, Texture*> BlocksTextures;
	map <IDs, Texture*> ItemsTextures;
	map <IDs, Block*> Blocks;
	map <IDs, Item*> Items;
	prepareBlocksTextures(BlocksTextures);
	prepareItemsTextures(ItemsTextures);
	prepareBlocksMap(Blocks, BlocksTextures);
	prepareItemsMap(Items, ItemsTextures);
	inventory = new Inventory(gameWindow, gameFont,BlocksTextures,ItemsTextures,Blocks,Items);
	Background background;

	/*Wooden_Sword sword1;
	Stone_Sword sword2;
	Gold_Sword sword3;
	sword1.setPosition(100, 100);
	sword2.setPosition(200, 100);
	sword3.setPosition(300, 100);*/
	//RenderWindow test(VideoMode::getDesktopMode(), "X", Style::Default);
	GameWorld world;
	/*world.items_on_ground.emplace_back(&sword1);
	world.items_on_ground.emplace_back(&sword2);
	world.items_on_ground.emplace_back(&sword3);*/
	Clock clock;
	world.dropItem(IDs::ChestID, BlocksTextures, ItemsTextures, Blocks, Items, player.getPosition());
	while (gameWindow.isOpen()) {
		//test.clear();
		//world.test(test);
		//test.display();

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
				inventory->checkSelectedItem();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and player.getIsAlive()) player.Up(0.02);
				//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.Down(0.02);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and player.getIsAlive()) player.Left(0.02);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and player.getIsAlive()) player.Right(0.02);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and player.getIsAlive()) {
					if (inventory->inv_vector[inventory->getQInventorySelected()].first != nullptr and inventory->selectedItem != nullptr and inventory->inv_vector[inventory->getQInventorySelected()].first->getItemType() == item_type::tool && inventory->getSelectedToolBlockDamage() == 0)
					{
						//inventory->inv_vector[inventory->getQInventorySelected()].first->Use();
						inventory->selectedItem->Use();
						if (gameWindow.mapPixelToCoords(Mouse::getPosition(gameWindow), gameWindow.getView()).x > player.getPosition().x)
							player.setScale({ (float)abs(player.getScale().x), player.getScale().y });
						else
							player.setScale({ (float)(-1) * abs(player.getScale().x), player.getScale().y });
					}
					else if(inventory->inv_vector[inventory->getQInventorySelected()].first != nullptr and inventory->selectedItem != nullptr and inventory->inv_vector[inventory->getQInventorySelected()].first->getItemType() == item_type::tool && inventory->getSelectedToolBlockDamage() != 0)
					{
						inventory->selectedItem->Use();
						player.DestroyBlock(world.world, gameWindow,inventory->getSelectedToolBlockDamage());
						if (player.isBlockDestroyed() == true) {
							world.dropItem(Blocks[player.getDestroyedBlockID()]->getDropID(), BlocksTextures,ItemsTextures, Blocks,Items,player.getDestroyedBlockPosition());
						}
					}
					else {
						player.DestroyBlock(world.world, gameWindow, inventory->getSelectedToolBlockDamage());
						if (player.isBlockDestroyed() == true) {
							world.dropItem(Blocks[player.getDestroyedBlockID()]->getDropID(), BlocksTextures, ItemsTextures, Blocks, Items, player.getDestroyedBlockPosition());
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
						case(Keyboard::Num2): {inventory->qInvSelect(1); break; }
						case(Keyboard::Num3): {inventory->qInvSelect(2); break; }
						case(Keyboard::Num4): {inventory->qInvSelect(3); break; }
						case(Keyboard::Num5): {inventory->qInvSelect(4); break; }
						case(Keyboard::Num6): {inventory->qInvSelect(5); break; }
						case(Keyboard::Num7): {inventory->qInvSelect(6); break; }
						case(Keyboard::Num8): {inventory->qInvSelect(7); break; }
						case(Keyboard::Num9): {inventory->qInvSelect(8); break; }
						case(Keyboard::Num0): {inventory->qInvSelect(9); break; }

						}
					}
					if (gameEvent.type == sf::Event::MouseButtonPressed and player.getIsAlive()) {
						if (gameEvent.key.code == Mouse::Right) {
							player.UseBlock(gameWindow, world.world);
							if (player.isChestOpened() == true) {
								currentGameMode = gameMode::inventory;
							}
							if (inventory->inv_vector[inventory->getQInventorySelected()].first != nullptr)
							{
								if (inventory->inv_vector[inventory->getQInventorySelected()].first->getItemType() == item_type::block)
								{
									player.EmplaceBlock(world.world, gameWindow, inventory->getQInventorySelectedID());
									if (player.isBlockPlaced() == true) {
										inventory->inv_vector[inventory->getQInventorySelected()].second--;
										if (inventory->getQInventorySelectedID() == IDs::ChestID) {
											world.chests.emplace_back( player.getPlacedBlockPosition(), vector<pair<unique_ptr<Item>, int>>() );
											for (int i = 1; i <= 24; i++) {
												world.chests.back().second.emplace_back(nullptr, 0);
											}
										}
									}
								}
							}
							
						}
					}
				}
				
				gameWindow.clear();
				background.Render(gameWindow);
				inventory->setIsCraftingTableNear(false);
				for (int i = max((int)player.getPosition().x - renderWidth * 16, 0); i < min((int)player.getPosition().x + renderWidth * 16, 16000); i += 16)
				{
					for (int j = max((int)player.getPosition().y - renderHeight * 16, 0); j < min((int)player.getPosition().y + renderHeight * 16, 16000); j += 16)
					{
						if (world.world[i / 16][j / 16].ID != IDs::AirID)
						{
							Blocks[world.world[i / 16][j / 16].ID]->setPosition(world.world[i / 16][j / 16].rect.left, world.world[i / 16][j / 16].rect.top);
							gameWindow.draw(*Blocks[world.world[i / 16][j / 16].ID]);
							if (world.world[i / 16][j / 16].ID == CraftingTableID && player.playerReach->intersects(world.world[i / 16][j / 16].rect)){
								
								inventory->setIsCraftingTableNear(true);
							}
							
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
					if (!entity->getIsPlayer()) entity->UpdateAI(elapsed.asSeconds(), player, world.world);
					entity->Update(elapsed.asSeconds());
					entity->Draw(gameWindow);
					if (!entity->getIsPlayer() and entity->getIsDeadTime() > 5)
					{
						delete entity;
						entities.erase(remove(entities.begin(), entities.end(), entity), entities.end());
					}
				}
				if (inventory->inv_vector[inventory->getQInventorySelected()].first != nullptr and inventory->selectedItem != nullptr and inventory->inv_vector[inventory->getQInventorySelected()].first->getItemType() == item_type::tool)
				{
					//inventory->inv_vector[inventory->getQInventorySelected()].first->Update(elapsed.asSeconds(), player, entities);
					//gameWindow.draw(*inventory->inv_vector[inventory->getQInventorySelected()].first);
					inventory->selectedItem->Update(elapsed.asSeconds(), player, entities);
					gameWindow.draw(*inventory->selectedItem);
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

				if (!player.getIsAlive())
				{
					deathScreenTime -= elapsed.asSeconds();
					deathScreen->update(deathScreenTime, gameWindow);
					deathScreen->display(gameWindow);

					if (deathScreenTime <= 0)
					{
						player.Respawn();
						//player.setPosition(0, 0);
						deathScreenTime = 10;
					}
				}
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
				inventory->displayInventory(gameWindow,player.isChestOpened());
				if (player.isChestOpened() == true) {
					for(auto &el : world.chests){
						if (el.first == player.getOpenedChestPosition()) {
							for (int i = 0; i < el.second.size();i++) {
								if (el.second[i].first != nullptr) {
									el.second[i].first->setPosition(Vector2f(inventory->getChestItemsPosition(i).x+4, inventory->getChestItemsPosition(i).y + 4));
									inventory->getChestItemQuantityText(i).setScale(0.5, 0.5);
									inventory->getChestItemQuantityText(i).setPosition(el.second[i].first->getPosition());
									inventory->getChestItemQuantityText(i).setString(to_string(el.second[i].second));
									gameWindow.draw(*el.second[i].first);
									gameWindow.draw(inventory->getChestItemQuantityText(i));
								}
								else{ inventory->getChestItemQuantityText(i).setString(""); }
							}
						}
				}

				}
				
				if (gameWindow.pollEvent(gameEvent)) {
					if (gameEvent.type == sf::Event::KeyPressed) {
						if (gameEvent.key.code == Keyboard::E) {
							currentGameMode = gameMode::playing;
							player.setChestOpened(false);
						}
						if (gameEvent.key.code == Keyboard::Escape) {
							currentGameMode = gameMode::pauseMenu;
							player.setChestOpened(false);
						}
						
					}

					else if (gameEvent.type == Event::MouseButtonPressed) {
						if (gameEvent.key.code == Mouse::Left) {
							if (player.isChestOpened() == true) {
								
								for (auto & el : world.chests) {
									if (el.first == player.getOpenedChestPosition() && inventory->isMouseOnChest(gameWindow) == true) {
										
										if (inventory->mouseItem.first == nullptr || el.second[inventory->getChestSelected()].first == nullptr) {
											inventory->mouseItem.swap(el.second[inventory->getChestSelected()]);
											
										}

										else if (inventory->mouseItem.first != nullptr && el.second[inventory->getChestSelected()].first != nullptr) {

											if (inventory->mouseItem.first->getID() != el.second[inventory->getChestSelected()].first->getID() && el.first == player.getOpenedChestPosition()) {
												inventory->mouseItem.swap(el.second[inventory->getChestSelected()]);
											}
											//	/*else if (inventory->mouseItem.first->getID() == world.chests[player.getOpenedChestPosition()][inventory->getChestSelected()].first->getID()) {
											//		if (inventory->mouseItem.second + world.chests[player.getOpenedChestPosition()][inventory->getChestSelected()].second < inventory->mouseItem.first->getStackingQuantity()) {
											//			world.chests[player.getOpenedChestPosition()][inventory->getChestSelected()].second += inventory->mouseItem.second;
											//			inventory->mouseItem.second -= inventory->mouseItem.second;
											//		}
											//		else {
											//			int difference = inventory->mouseItem.first->getStackingQuantity() - world.chests[player.getOpenedChestPosition()][inventory->getChestSelected()].second;
											//			if (difference > 0) {
											//				world.chests[player.getOpenedChestPosition()][inventory->getChestSelected()].second += difference;
											//				inventory->mouseItem.second -= difference;
											//			}
											//			else { inventory->mouseItem.swap(world.chests[player.getOpenedChestPosition()][inventory->getChestSelected()]); }

											//		}
											//	}*/
										}
									}

								}

							}
							if (inventory->isMouseOnInventory(gameWindow) == true) {
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

							}
							if (inventory->isMouseOnCrafitng() == true && player.isChestOpened() == false) {
								inventory->setCraftSelected(inventory->getMouseOnCraft(),BlocksTextures,ItemsTextures,Blocks,Items,gameFont);
										
							}
						}
						else if(gameEvent.key.code == Mouse::Right && inventory->isAbleToCraft() == true && player.isChestOpened() == false)
							 {
							for (auto& ite : inventory->itemsToCraft[inventory->getCraftSelected()]->getItemsRequiredToCraft()) {
								auto i = find_if(inventory->inv_vector.begin(), inventory->inv_vector.end(), [&ite](auto& it) {if (it.first != nullptr) { return ite.first == it.first->getID() && it.second >= ite.second; } });
								if (i != inventory->inv_vector.end()) {
									i->second -= ite.second;
								}
							}
							for (int i = 1; i <= inventory->itemsToCraft[inventory->getCraftSelected()]->getCraftedQuantity(); i++) {
								world.dropItem(inventory->itemsToCraft[inventory->getCraftSelected()]->getID(), BlocksTextures, ItemsTextures, Blocks,Items ,player.getPosition());
							}
						}
					}
				}
				
				
			}
			
			gameWindow.display();
	}
	
}



