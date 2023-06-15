#include "Game.h"

float getPlayerDistance(Vector2f player, Vector2f entity)
{
	return sqrt((player.x - entity.x) * (player.x - entity.x) + (player.y - entity.y) * (player.y - entity.y));
}

void Game::initFont()
{
	if (!gameFont.loadFromFile("Fonts/font.ttf")) { cout << "No font file found"; }
	if (!gameMusic.openFromFile("Textures/gameMusic.wav")) { cout << "No wav file found"; }
	gameMusic.setVolume(20);
	bufferItemPickUp.loadFromFile("Textures/grab.wav");
	bufferInventoryOpen.loadFromFile("Textures/inventoryOpen.wav");
	bufferInventoryClose.loadFromFile("Textures/inventoryClose.wav");
	soundItemPickUp.setBuffer(bufferItemPickUp);
	soundInventoryOpen.setBuffer(bufferInventoryOpen);
	soundInventoryClose.setBuffer(bufferInventoryClose);
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
	if (gameWindow.getView().getCenter().x - gameWindow.getView().getSize().x / 2 < 0)
	{
		View pom = gameWindow.getView();
		pom.setCenter(gameWindow.getView().getSize().x / 2, gameWindow.getView().getCenter().y);
		gameWindow.setView(pom);
	}
	else if (gameWindow.getView().getCenter().x + gameWindow.getView().getSize().x / 2 > 16 * 1000)
	{
		View pom = gameWindow.getView();
		pom.setCenter(16 * 1000 - gameWindow.getView().getSize().x / 2, gameWindow.getView().getCenter().y);
		gameWindow.setView(pom);
	}

	if (gameWindow.getView().getCenter().y - gameWindow.getView().getSize().y / 2 < 0)
	{
		View pom = gameWindow.getView();
		pom.setCenter(gameWindow.getView().getCenter().x, gameWindow.getView().getSize().y / 2);
		gameWindow.setView(pom);
	}
	else if (gameWindow.getView().getCenter().x + gameWindow.getView().getSize().x / 2 > 16 * 1000)
	{
		View pom = gameWindow.getView();
		pom.setCenter(gameWindow.getView().getCenter().x, 16 * 1000 - gameWindow.getView().getSize().y / 2);
		gameWindow.setView(pom);
	}
}

void Game::updateItemsOnTheGround(GameWorld & world,Time &elapsed)
{
	for (auto& item : world.items_on_ground)
	{
		if (item != nullptr and (item->getPosition().x > player.getPosition().x - renderWidth * 16 and item->getPosition().x < player.getPosition().x + renderWidth * 16 and item->getPosition().y > player.getPosition().y - renderHeight * 16 and item->getPosition().y < player.getPosition().y + renderHeight * 16))
		{
			player.updatePickUpRange();
			if (item->getGlobalBounds().intersects(player.getPlayerPickUpRange()) && inventory->isInventoryFull(item->getID()) == false) {
				item->goToPlayer(player.getPosition());
				if (item->getGlobalBounds().intersects(player.getGlobalBounds())) {
					soundItemPickUp.play();
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
	entities.push_back(new Skeleton);
	entities.push_back(new Mushroom);
	entities.push_back(new Slime);
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
	world.dropItem(IDs::GoldID, BlocksTextures, ItemsTextures, Blocks, Items, player.getPosition());
	world.dropItem(IDs::ChestID, BlocksTextures, ItemsTextures, Blocks, Items, player.getPosition());
	world.dropItem(IDs::FurnaceID, BlocksTextures, ItemsTextures, Blocks, Items, player.getPosition());
	world.dropItem(IDs::IronIngotID, BlocksTextures, ItemsTextures, Blocks, Items, player.getPosition());
	world.dropItem(IDs::DiamondItemID, BlocksTextures, ItemsTextures, Blocks, Items, player.getPosition());
	world.dropItem(IDs::EmeraldItemID, BlocksTextures, ItemsTextures, Blocks, Items, player.getPosition());
	world.dropItem(IDs::IronPickaxeID, BlocksTextures, ItemsTextures, Blocks, Items, player.getPosition());
	world.dropItem(IDs::DiamondPickaxeID, BlocksTextures, ItemsTextures, Blocks, Items, player.getPosition());
	world.dropItem(IDs::IronSwordID, BlocksTextures, ItemsTextures, Blocks, Items, player.getPosition());
	world.dropItem(IDs::DiamondSwordID, BlocksTextures, ItemsTextures, Blocks, Items, player.getPosition());
	while (gameWindow.isOpen()) {
		//test.clear();
		//world.test(test);
		//test.display();

			Time elapsed = clock.restart();
			


			if (currentGameMode == gameMode::mainMenu) {
				mainMenu->musicOn();

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
				appleUseTime -= elapsed.asSeconds();
				world.GenerateEntities(elapsed.asSeconds(), player, entities);
				mainMenu->musicOff();
				if (gameMusic.getStatus() != Music::Playing)
				{
					gameMusic.setLoop(true);
					gameMusic.play();
				}
				setGameView();
				inventory->checkSelectedItem();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and player.getIsAlive()) player.Up(0.02);
				//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.Down(0.02);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and player.getIsAlive()) player.Left(0.02);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and player.getIsAlive()) player.Right(0.02);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and player.getIsAlive()) {
					if (inventory->inv_vector[inventory->getQInventorySelected()].first != nullptr and inventory->selectedItem != nullptr and (inventory->inv_vector[inventory->getQInventorySelected()].first->getItemType() == item_type::tool or inventory->inv_vector[inventory->getQInventorySelected()].first->getItemType() == item_type::material) && inventory->getSelectedToolBlockDamage() == 0)
					{
						//inventory->inv_vector[inventory->getQInventorySelected()].first->Use();
						inventory->selectedItem->Use();
						if (inventory->selectedItem->getID() == IDs::AppleID and appleUseTime < 0)
						{
							player.Heal(40);
							player.soundEat.play();
							inventory->inv_vector[inventory->getQInventorySelected()].second--;
							appleUseTime = 1;
						}
						else if (inventory->selectedItem->getItemType() == item_type::tool) player.Attack(0, player);
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
							if (player.getDestroyedBlockID() == ChestID) {
								auto a = find_if(world.chests.begin(), world.chests.end(), [this](const pair<Vector2f, vector<pair<unique_ptr<Item>, int>>>& chest) {return chest.first == player.getDestroyedBlockPosition(); });
								world.chests.erase(a);
							}
						}
						
					}
					else if (inventory->inv_vector[inventory->getQInventorySelected()].first != nullptr and inventory->selectedItem->getID() == IDs::AppleID) {}
					else {
						player.DestroyBlock(world.world, gameWindow, inventory->getSelectedToolBlockDamage());
						if (player.isBlockDestroyed() == true) {
							world.dropItem(Blocks[player.getDestroyedBlockID()]->getDropID(), BlocksTextures, ItemsTextures, Blocks, Items, player.getDestroyedBlockPosition());
							if (player.getDestroyedBlockID() == ChestID) {
								auto a = find_if(world.chests.begin(), world.chests.end(), [this](const pair<Vector2f, vector<pair<unique_ptr<Item>, int>>>& chest) {return chest.first == player.getDestroyedBlockPosition(); });
								world.chests.erase(a);
							}
						}
					}
				}
				if (gameWindow.pollEvent(gameEvent)) {
					if (gameEvent.type == sf::Event::MouseWheelMoved)
					{
						int select;
						if (gameEvent.mouseWheel.delta > 0)
						{
							if (inventory->getQInventorySelected() + 1 > 9) select = 0;
							else select = inventory->getQInventorySelected() + 1;
						}
						else if (gameEvent.mouseWheel.delta < 0)
						{
							if (inventory->getQInventorySelected() - 1 < 0) select = 9;
							else select = inventory->getQInventorySelected() - 1;
						}
						inventory->qInvSelect(select);
					}
					if (gameEvent.type == sf::Event::KeyPressed) {
						if (gameEvent.key.code == Keyboard::Escape) {
					
							currentGameMode = gameMode::pauseMenu;
						}
						else if (gameEvent.key.code == Keyboard::E) {
							
							currentGameMode = gameMode::inventory;
							soundInventoryOpen.play();
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
								soundInventoryOpen.play();
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
				inventory->setIsFurnaceNear(false);
				for (int i = gameWindow.getView().getCenter().x - gameWindow.getView().getSize().x / 2; i < gameWindow.getView().getCenter().x + gameWindow.getView().getSize().x / 2 + 16; i += 16)
				{
					for (int j = gameWindow.getView().getCenter().y - gameWindow.getView().getSize().y / 2; j < gameWindow.getView().getCenter().y + gameWindow.getView().getSize().y / 2 + 16; j += 16)
					{
						if (world.world[i / 16][j / 16].ID != IDs::AirID)
						{
							Blocks[world.world[i / 16][j / 16].ID]->setPosition(world.world[i / 16][j / 16].rect.left, world.world[i / 16][j / 16].rect.top);
							gameWindow.draw(*Blocks[world.world[i / 16][j / 16].ID]);
							if (world.world[i / 16][j / 16].ID == CraftingTableID && player.playerReach->intersects(world.world[i / 16][j / 16].rect)){
								
								inventory->setIsCraftingTableNear(true);
							}
							if (world.world[i / 16][j / 16].ID == FurnaceID && player.playerReach->intersects(world.world[i / 16][j / 16].rect)) {

								inventory->setIsFurnaceNear(true);
							}
							
						}
					}
				}
			
				for (auto entity : entities)
				{
					entity->GravityUpdate(0.02, 20);
					if (!entity->getIsPlayer()) entity->UpdateAI(elapsed.asSeconds(), player, world.world);
					for (int i = max((int)entity->getPosition().x - collisionsCheckWidth * 16, 0); i < min((int)entity->getPosition().x + collisionsCheckWidth * 16, 16000); i += 16)
					{
						for (int j = max((int)entity->getPosition().y - collisionsCheckHeight * 16, 0); j < min((int)entity->getPosition().y + collisionsCheckHeight * 16, 16000); j += 16)
						{
							entity->CheckCollisions(&world.world[i / 16][j / 16].rect);
						}
					}
					entity->playerDistance = getPlayerDistance(player.getPosition(), entity->getPosition());
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
				updateItemsOnTheGround(world,elapsed);
				
				world.drawItemsOnGround(gameWindow, player.getPosition(), renderWidth, renderHeight);

				/*rectangle.setFillColor(sf::Color::Transparent);
				rectangle.setOutlineThickness(1);
				rectangle.setOutlineColor(Color::White);
				rectangle.setPosition(entities[3]->getGlobalBounds().left, entities[3]->getGlobalBounds().top);
				rectangle.setSize(Vector2f(entities[3]->getGlobalBounds().width, entities[3]->getGlobalBounds().height));
				gameWindow.draw(rectangle);*/
				
				
				
				player.updateReach();
			
				inventory->displayQInventory(gameWindow);

				if (!player.getIsAlive())
				{
					currentGameMode = gameMode::dead;
				}
			}
			else if (currentGameMode == gameMode::dead)
			{
				deathScreenTime -= elapsed.asSeconds();
				deathScreen->update(deathScreenTime, gameWindow);
				deathScreen->display(gameWindow);

				if (deathScreenTime <= 0)
				{
					currentGameMode = gameMode::playing;
					player.Respawn();
					//player.setPosition(0, 0);
					deathScreenTime = 10;
				}
			}
			else if (currentGameMode == gameMode::pauseMenu) {
				mainMenu->musicOff();
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
				mainMenu->musicOff();
				setGameView();
				gameWindow.clear();
				background.Render(gameWindow);
				for (int i = gameWindow.getView().getCenter().x - gameWindow.getView().getSize().x / 2; i < gameWindow.getView().getCenter().x + gameWindow.getView().getSize().x / 2 + 16; i += 16)
				{
					for (int j = gameWindow.getView().getCenter().y - gameWindow.getView().getSize().y / 2; j < gameWindow.getView().getCenter().y + gameWindow.getView().getSize().y / 2 + 16; j += 16)
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
				updateItemsOnTheGround(world, elapsed);
				inventory->displayInventory(gameWindow,player.isChestOpened());
				if (player.isChestOpened() == true) {
					for(auto &el : world.chests){
						if (el.first == player.getOpenedChestPosition()) {
							for (int i = 0; i < el.second.size();i++) {
								if (el.second[i].first != nullptr) {
									el.second[i].first->setPosition(Vector2f(inventory->getChestItemsPosition(i).x+4, inventory->getChestItemsPosition(i).y + 4));
									inventory->setChestItemQuantityTextString(to_string(el.second[i].second), i);
									inventory->setChestItemQuantityTextPosition(Vector2f(el.second[i].first->getPosition().x+1, el.second[i].first->getPosition().y-6),i);
									inventory->setChestItemQuantityTextScale(0.5,0.5, i);
									gameWindow.draw(*el.second[i].first);
									gameWindow.draw(inventory->getChestItemQuantityText(i));
								}
								else{ inventory->getChestItemQuantityText(i).setString(""); }
							}
						}
				    }

				}
				if (inventory->mouseItem.first != nullptr) {
					gameWindow.draw(*inventory->mouseItem.first);
					gameWindow.draw(inventory->mouseItemQuantity);


				}
				
				if (gameWindow.pollEvent(gameEvent)) {
					if (gameEvent.type == sf::Event::KeyPressed) {
						if (gameEvent.key.code == Keyboard::E) {
							currentGameMode = gameMode::playing;
							soundInventoryClose.play();
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
												else if (inventory->mouseItem.first->getID() == el.second[inventory->getChestSelected()].first->getID()) {
													if (inventory->mouseItem.second + el.second[inventory->getChestSelected()].second < inventory->mouseItem.first->getStackingQuantity()) {
														el.second[inventory->getChestSelected()].second += inventory->mouseItem.second;
														inventory->mouseItem.second -= inventory->mouseItem.second;
													}
													else {
														int difference = inventory->mouseItem.first->getStackingQuantity() - el.second[inventory->getChestSelected()].second;
														if (difference > 0) {
															el.second[inventory->getChestSelected()].second += difference;
															inventory->mouseItem.second -= difference;
														}
														else { inventory->mouseItem.swap(el.second[inventory->getChestSelected()]); }

													}
												}
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
							if ((inventory->isMouseOnInventory(gameWindow) == false  && inventory->getMouseOnCraft() == -1 ) && player.isChestOpened() == false && inventory->isMouseOnCraftingRequired(gameWindow) == false) {
								if (Mouse::getPosition().x > gameWindow.getSize().x / 2) {
									for (int i = 1; i <= inventory->mouseItem.second; i++) {
										world.dropItem(inventory->mouseItem.first->getID(), BlocksTextures, ItemsTextures, Blocks, Items, Vector2f(player.getPosition().x + 50, player.getPosition().y));
									}
								}
								else if (Mouse::getPosition().x < gameWindow.getSize().x / 2){
									for (int i = 1; i <= inventory->mouseItem.second; i++) {
										world.dropItem(inventory->mouseItem.first->getID(), BlocksTextures, ItemsTextures, Blocks, Items, Vector2f(player.getPosition().x - 75, player.getPosition().y));
									}
								}
								inventory->mouseItem.second = 0;
							}
							else if ((inventory->isMouseOnInventory(gameWindow) == false && inventory->isMouseOnChest(gameWindow) == false) && player.isChestOpened() == true) {
								if (Mouse::getPosition().x > gameWindow.getSize().x / 2) {
									for (int i = 1; i <= inventory->mouseItem.second; i++) {
										world.dropItem(inventory->mouseItem.first->getID(), BlocksTextures, ItemsTextures, Blocks, Items, Vector2f(player.getPosition().x + 50, player.getPosition().y));
									}
								}
								else if (Mouse::getPosition().x < gameWindow.getSize().x / 2) {
									for (int i = 1; i <= inventory->mouseItem.second; i++) {
										world.dropItem(inventory->mouseItem.first->getID(), BlocksTextures, ItemsTextures, Blocks, Items, Vector2f(player.getPosition().x - 75, player.getPosition().y));
									}
								}
								inventory->mouseItem.second = 0;
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



