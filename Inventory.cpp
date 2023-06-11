#include "Inventory.h"


void Inventory::initFont(Font& gameFont)
{
	for (int i = 0; i < 40; i++) {
		itemQuantity[i].setFont(gameFont);
	}
	mouseItemQuantity.setFont(gameFont);
	craftedItemQuantity.setFont(gameFont);
	itemsRequired.setFont(gameFont);
}

void Inventory::initTextures()
{
	if (!invTexture.loadFromFile("Textures/inventory.png")) { cout << "No inv found" << endl; }
	if (!qInvTexture.loadFromFile("Textures/qInventory.png")) { cout << "No q inv found" << endl; }
	if (!invSTexture.loadFromFile("Textures/inventorySelect.png")) { cout << "No inv selected found" << endl; }
	if (!craftingSlotTexture.loadFromFile("Textures/Inventory_Slot.png")) { cout << "No crafting slot found" << endl; }
	if (!requiredBackground.loadFromFile("Textures/Inventory_background.png")) { cout << "No req background found" << endl; }
	if (!y_n.loadFromFile("Textures/no_yes.png")) { cout << "No y_n found" << endl; }
}


void Inventory::initSprites(RenderWindow& gameWindow)
{
	invSprite.setTexture(invTexture);
	invSprite.setScale(2, 2);
	qInvSprite.setTexture(qInvTexture);
	qInvSprite.setScale(1, 1);
	invSSprite.setTexture(invSTexture);
	invSSprite.setScale(invSprite.getScale());
	craftingSelectedSprite.setTexture(invSTexture);
	craftingSelectedSprite.setScale(3, 3);
	reqBackground.setTexture(requiredBackground);
	reqBackground.setScale(2, 2);
	no_yes.setTexture(y_n);
	no_yes.setScale(1.59, 1.59);
	isAbleToCraftYN.setTexture(y_n);
	
}

void Inventory::initTexts()
{
	itemsRequired.setString("Items Required");
	itemsRequired.setCharacterSize(50);
	itemsRequired.setScale(0.28, 0.28);
	craftedItemQuantity.setCharacterSize(50);
	craftedItemQuantity.setScale(0.4, 0.4);
}



void Inventory::updateInventory(RenderWindow& gameWindow)
{
	mouseOnCrafting = false;
	mouseOnCraft = -1;
	invSprite.setPosition(gameWindow.getView().getCenter().x - (invSprite.getScale().x * 101.f), gameWindow.getView().getCenter().y - (invSprite.getScale().x * 68.f));
	/*invSquare[40].top = invSprite.getPosition().y + 12 + 2;
	invSquare[40].left = invSprite.getPosition().x + 12 + 2;
	invSquare[41].top = invSprite.getPosition().y + 12 + invSquare[0].height + 4;
	invSquare[41].left = invSprite.getPosition().x + 12 + 2;
	invSquare[42].top = invSprite.getPosition().y + 12 + 2;
	invSquare[42].left = invSprite.getPosition().x + 12 + 2 + 96;
	invSquare[43].top = invSprite.getPosition().y + 12 + invSquare[0].height + 4;
	invSquare[43].left = invSprite.getPosition().x + 12 + 2 + 96;*/
	invSSprite.setScale(invSprite.getScale());
	for (int i = 0; i < 40; i++) {
		invSquare[i].width = invSSprite.getGlobalBounds().width - 4;
		invSquare[i].height = invSSprite.getGlobalBounds().height - 4;
	}

	invSquare[0].top = invSprite.getPosition().y + 12 + (invSquare[0].height + 4) * 5 + 10;
	invSquare[0].left = invSprite.getPosition().x + 12 + 2;

	for (int i = 1; i <= 9; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + (invSquare[0].height + 4) * 5 + 10;
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
	}
	invSquare[10].top = invSprite.getPosition().y + 12 + 2;
	invSquare[10].left = invSprite.getPosition().x + 12 + 2 + 96 + invSquare[0].width + 20;
	for (int i = 11; i <= 15; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + 2;
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
	}
	invSquare[16].top = invSprite.getPosition().y + 12 + 2 + invSquare[0].height + 2;
	invSquare[16].left = invSprite.getPosition().x + 12 + 2 + 96 + invSquare[0].width + 20;
	for (int i = 17; i <= 21; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + 2 + invSquare[0].height + 2;
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
	}
	invSquare[22].top = invSprite.getPosition().y + 12 + 2 + 2 * (invSquare[0].height + 2);
	invSquare[22].left = invSprite.getPosition().x + 12 + 2 + 96 + invSquare[0].width + 20;
	for (int i = 23; i <= 27; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + 2 + 2 * (invSquare[0].height + 2);
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
	}
	invSquare[28].top = invSprite.getPosition().y + 12 + 2 + 3 * (invSquare[0].height + 2);
	invSquare[28].left = invSprite.getPosition().x + 12 + 2 + 96 + invSquare[0].width + 20;
	for (int i = 29; i <= 33; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + 2 + 3 * (invSquare[0].height + 2);
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
	}
	invSquare[34].top = invSprite.getPosition().y + 12 + 2 + 4 * (invSquare[0].height + 2);
	invSquare[34].left = invSprite.getPosition().x + 12 + 2 + 96 + invSquare[0].width + 20;
	for (int i = 35; i <= 39; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + 2 + 4 * (invSquare[0].height + 2);
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
	}


	for (int i = 0; i < inv_vector.size(); i++) {
		if (inv_vector[i].first != nullptr) {
			inv_vector[i].first->setPosition(invSquare[i].left + 4, invSquare[i].top + 4);
			inv_vector[i].first->setScale(1.75, 1.75);
		}
	}

	for (int i = 0; i < 40; i++) {
		if (inv_vector[i].second == 0) {
			inv_vector[i].first = nullptr;

		}
		if (inv_vector[i].first == nullptr) {
			inv_vector[i].second = 0;
		}
		if (inv_vector[i].first != nullptr) {

			itemQuantity[i].setScale(0.5, 0.5);
			itemQuantity[i].setPosition(inv_vector[i].first->getPosition().x + 1, inv_vector[i].first->getPosition().y - 6);
			itemQuantity[i].setString(to_string(inv_vector[i].second));


		}
		else { itemQuantity[i].setString(""); }
	}
	if (mouseItem.first != nullptr) {
		Vector2f worldPos = gameWindow.mapPixelToCoords(Mouse::getPosition(gameWindow), gameWindow.getView());

		mouseItem.first->setPosition(worldPos.x - float(mouseItem.first->getGlobalBounds().width / 2), worldPos.y - float(mouseItem.first->getGlobalBounds().height / 2));
		mouseItemQuantity.setScale(0.5, 0.5);
		mouseItemQuantity.setPosition(worldPos.x-float(mouseItem.first->getGlobalBounds().width/2)+1, worldPos.y - float(mouseItem.first->getGlobalBounds().height / 2)-6);
		mouseItemQuantity.setString(to_string(mouseItem.second));


	}
	if (mouseItem.second == 0) {
		mouseItem.first = nullptr;
	}

	craftingSelectedSprite.setPosition(invSprite.getPosition().x + 530, invSprite.getPosition().y + 100);

	itemsToCraft[craftSelected]->setPosition(craftingSelectedSprite.getPosition().x + 10, craftingSelectedSprite.getPosition().y + 10);

	for (int i = craftSelected-1; i >= 0; i--) {
		itemsToCraft[i]->setPosition(craftingSelectedSprite.getPosition().x+10, craftingSelectedSprite.getPosition().y+10 - ((craftSelected - i) * (craftingSelectedSprite.getGlobalBounds().height-3)));
	}
	for (int i = craftSelected + 1; i<itemsToCraft.size(); i++) {
		itemsToCraft[i]->setPosition(craftingSelectedSprite.getPosition().x + 10, craftingSelectedSprite.getPosition().y+10 + ((i-craftSelected) * (craftingSelectedSprite.getGlobalBounds().height-3)));
	}
	for (int i = 0; i < slotSprites.size(); i++) {
		slotSprites[i]->setPosition(itemsToCraft[i]->getPosition().x - 10, itemsToCraft[i]->getPosition().y - 10);

	}

	for (int i = 0; i < slotSprites.size(); i++) {
		itemsToCraft[i]->setColor(itemsToCraft[craftSelected]->getColor());
		slotSprites[i]->setColor(itemsToCraft[craftSelected]->getColor());
	}

	reqBackground.setPosition(invSprite.getGlobalBounds().left + invSprite.getGlobalBounds().width, invSprite.getGlobalBounds().top);
	itemsRequired.setPosition(reqBackground.getPosition().x+5, reqBackground.getPosition().y -1);
	



	for (int i = 0; i < itemsRequiredToCraft.size();i++) {
		if (i < 3) {
			itemsRequiredToCraft[i]->setPosition(reqBackground.getPosition().x + 10 + (i * (itemsRequiredToCraft[i]->getGlobalBounds().width + 4)), reqBackground.getPosition().y + 20);
			itemsRequiredToCraftQuantity[i]->setPosition(itemsRequiredToCraft[i]->getPosition().x + 1, itemsRequiredToCraft[i]->getPosition().y - 8);
		}
		if (i >= 3&& i<6) {
			itemsRequiredToCraft[i]->setPosition(reqBackground.getPosition().x + 10 + ((i-3) * (itemsRequiredToCraft[i]->getGlobalBounds().width + 4)), reqBackground.getPosition().y + 20 + (itemsRequiredToCraft[i]->getGlobalBounds().height + 3));
			itemsRequiredToCraftQuantity[i]->setPosition(itemsRequiredToCraft[i]->getPosition().x + 1, itemsRequiredToCraft[i]->getPosition().y - 8);
		}
		if (i >= 6 && i < 9) {
			itemsRequiredToCraft[i]->setPosition(reqBackground.getPosition().x + 10 + ((i - 6) * (itemsRequiredToCraft[i]->getGlobalBounds().width + 4)), reqBackground.getPosition().y + 20 + 2*(itemsRequiredToCraft[i]->getGlobalBounds().height + 3));
			itemsRequiredToCraftQuantity[i]->setPosition(itemsRequiredToCraft[i]->getPosition().x + 1, itemsRequiredToCraft[i]->getPosition().y - 8);
		}
		if (i >= 9 && i < 12) {
			itemsRequiredToCraft[i]->setPosition(reqBackground.getPosition().x + 10 + ((i - 9) * (itemsRequiredToCraft[i]->getGlobalBounds().width + 4)), reqBackground.getPosition().y + 20 + 3*(itemsRequiredToCraft[i]->getGlobalBounds().height + 3));
			itemsRequiredToCraftQuantity[i]->setPosition(itemsRequiredToCraft[i]->getPosition().x + 1, itemsRequiredToCraft[i]->getPosition().y - 8);
		}
		if (i >= 12 && i < 15) {
			itemsRequiredToCraft[i]->setPosition(reqBackground.getPosition().x + 10 + ((i - 12) * (itemsRequiredToCraft[i]->getGlobalBounds().width + 4)), reqBackground.getPosition().y + 20 + 4 * (itemsRequiredToCraft[i]->getGlobalBounds().height + 3));
			itemsRequiredToCraftQuantity[i]->setPosition(itemsRequiredToCraft[i]->getPosition().x + 1, itemsRequiredToCraft[i]->getPosition().y - 8);
		}
		if (i >= 15 && i < 18) {
			itemsRequiredToCraft[i]->setPosition(reqBackground.getPosition().x + 10 + ((i - 15) * (itemsRequiredToCraft[i]->getGlobalBounds().width + 4)), reqBackground.getPosition().y + 20 + 5* (itemsRequiredToCraft[i]->getGlobalBounds().height + 3));
			itemsRequiredToCraftQuantity[i]->setPosition(itemsRequiredToCraft[i]->getPosition().x + 1, itemsRequiredToCraft[i]->getPosition().y - 8);
		}
		/*if (i >= 18 && i < 21) {
			itemsRequiredToCraft[i]->setPosition(reqBackground.getPosition().x + 10 + ((i - 18) * (itemsRequiredToCraft[i]->getGlobalBounds().width + 4)), reqBackground.getPosition().y + 20 + 6 * (itemsRequiredToCraft[i]->getGlobalBounds().height + 3));
			itemsRequiredToCraftQuantity[i]->setPosition(itemsRequiredToCraft[i]->getPosition().x + 1, itemsRequiredToCraft[i]->getPosition().y - 8);
		}*/
		itemsRequiredToCraft[i]->setScale(2, 2);
	}

	craftedItemQuantity.setString(to_string(itemsToCraft[craftSelected]->getCraftedQuantity()));
	craftedItemQuantity.setPosition(itemsToCraft[craftSelected]->getPosition().x+1, itemsToCraft[craftSelected]->getPosition().y-8);


	craftingTableRequired->setPosition(reqBackground.getPosition().x + 10, reqBackground.getPosition().y + 20 + 6 * (itemsRequiredToCraft[0]->getGlobalBounds().height + 3));
	no_yes.setPosition(craftingTableRequired->getPosition());
	isAbleToCraftYN.setPosition(itemsToCraft[craftSelected]->getPosition().x+19, itemsToCraft[craftSelected]->getPosition().y + 19);
}


void Inventory::updateQInventory(RenderWindow& gameWindow)
{
	invSSprite.setScale(qInvSprite.getScale());
	qInvSprite.setPosition(gameWindow.getView().getCenter().x - (invSprite.getScale().x * 203.f * 0.95f), gameWindow.getView().getCenter().y - (invSprite.getScale().x * 32.f * 3.25));

	for (int i = 0; i <= 9; i++) {
		invSquare[i].width = invSSprite.getGlobalBounds().width - 4;
		invSquare[i].height = invSSprite.getGlobalBounds().height - 4;
	}

	invSquare[0].top = qInvSprite.getPosition().y + 8;
	invSquare[0].left = qInvSprite.getPosition().x + 8;

	for (int i = 1; i <= 9; i++) {
		invSquare[i].top = qInvSprite.getPosition().y + 8;
		invSquare[i].left = invSquare[i - 1].left + invSquare[i].width + 3;
	}

	for (int i = 0; i <= 9; i++) {
		if (inv_vector[i].first != nullptr) {
			inv_vector[i].first->setPosition(invSquare[i].left + 1, invSquare[i].top + 1);
			inv_vector[i].first->setScale(0.88, 0.86);
		}
	}

	for (int i = 0; i <= 9; i++) {
		if (inv_vector[i].second == 0) {
			inv_vector[i].first = nullptr;
		}
		if (inv_vector[i].first == nullptr) {
			inv_vector[i].second = 0;
		}
		if (inv_vector[i].first != nullptr) {

			itemQuantity[i].setScale(0.25, 0.25);
			itemQuantity[i].setPosition(inv_vector[i].first->getPosition().x + 1, inv_vector[i].first->getPosition().y - 3);
			itemQuantity[i].setString(to_string(inv_vector[i].second));


		}
		else { itemQuantity[i].setString(""); }
	}
	
}


void Inventory::initInventory(map <IDs, sf::Texture*>& arg1, map <IDs, sf::Texture*>& arg4, map <IDs, Block*>& arg2, map <IDs, Item*>& arg3,Font& gameFont)
{
	for (int i = 1; i <= 44;i++) {
		inv_vector.emplace_back(nullptr, 0);

	}
	mouseItem.first = nullptr;
	mouseItem.second = 0;

	
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::PlankID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::CraftingTableID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::ChestID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Material_Item(IDs::StickID,arg4, arg3, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Tool_Item(IDs::WoodenSwordID, arg4, arg3, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Tool_Item(IDs::StoneSwordID, arg4, arg3, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Tool_Item(IDs::WoodenPickaxeID, arg4, arg3, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Tool_Item(IDs::StonePickaxeID, arg4, arg3, craftingSelectedSprite.getPosition()));

	for (int i = 0; i < itemsToCraft.size(); i++) {
		slotSprites.emplace_back(new Sprite);
		slotSprites[i]->setTexture(craftingSlotTexture);
	}
	itemsRequiredToCraft.emplace_back(new Block_Item(arg1, arg2, itemsToCraft[craftSelected]->getItemsRequiredToCraft()[0].first, craftingSelectedSprite.getPosition()));
	itemsRequiredToCraftQuantity.emplace_back(new Text);
	itemsRequiredToCraftQuantity[0]->setFont(gameFont);
	itemsRequiredToCraftQuantity[0]->setString(to_string(itemsToCraft[craftSelected]->getItemsRequiredToCraft()[0].second));
	itemsRequiredToCraftQuantity[0]->setCharacterSize(50);
	itemsRequiredToCraftQuantity[0]->setScale(0.4, 0.4);
	craftingTableRequired = unique_ptr<Item>(new  Block_Item(arg1, arg2, IDs::CraftingTableID, craftingSelectedSprite.getPosition()));
	craftingTableRequired->setScale(2, 2);
	
}

void Inventory::craftSelect(RenderWindow& gameWindow)
{
	Vector2f worldPos = gameWindow.mapPixelToCoords(Mouse::getPosition(gameWindow), gameWindow.getView());
	for (int i = 0; i <itemsToCraft.size(); i++) {
		if (worldPos.x > itemsToCraft[i]->getGlobalBounds().left && worldPos.x < (itemsToCraft[i]->getGlobalBounds().left + itemsToCraft[i]->getGlobalBounds().width) && worldPos.y > itemsToCraft[i]->getGlobalBounds().top && worldPos.y < itemsToCraft[i]->getGlobalBounds().top + itemsToCraft[i]->getGlobalBounds().height) {
			mouseOnCraft = i;
			if (mouseOnCraft != craftSelected) {
				mouseOnCrafting = true;
			}
		}

	}
}

Inventory::Inventory(RenderWindow& gameWindow, Font& gameFont, map <IDs, sf::Texture*>& arg1, map <IDs, sf::Texture*>& arg4, map <IDs, Block*>& arg2, map <IDs, Item*>& arg3)
{
	qInvSelected = 0;
	craftSelected = 0;
	initFont(gameFont);
	initTextures();
	initSprites(gameWindow);
	initInventory(arg1,arg4,arg2,arg3,gameFont);
	initTexts();
}

void Inventory::displayInventory(RenderWindow& gameWindow)
{
	updateInventory(gameWindow);
	gameWindow.draw(invSprite);
	displayInventorySelected(gameWindow);

	for (auto& it : inv_vector) {
		if (it.first != nullptr) {
			gameWindow.draw(*it.first);
		}
	}
	

	for (int i = 0; i < 40; i++) {
		gameWindow.draw(itemQuantity[i]);
	}
	if (mouseItem.first != nullptr) {
		gameWindow.draw(*mouseItem.first);
		gameWindow.draw(mouseItemQuantity);

		
	}
	for (int i = 0; i < slotSprites.size(); i++) {
		slotSprites[i]->setScale(3, 3);
		if (itemsToCraft[i]->getPosition().y <= craftingSelectedSprite.getPosition().y + 10 - (4 * (craftingSelectedSprite.getGlobalBounds().height - 3))) {
			slotSprites[i]->setColor(Color(0, 0, 0, 0));
		}
		if (itemsToCraft[i]->getPosition().y >= craftingSelectedSprite.getPosition().y + 10 + (4 * (craftingSelectedSprite.getGlobalBounds().height - 3))) {
			slotSprites[i]->setColor(Color(0, 0, 0, 0));
		}
		
		gameWindow.draw(*slotSprites[i]);

	}
	

	
	for (int i = 0; i < itemsToCraft.size(); i++) {
		itemsToCraft[i]->setScale(2.5, 2.5);
		if (itemsToCraft[i]->getPosition().y <= craftingSelectedSprite.getPosition().y + 10 - (4 * (craftingSelectedSprite.getGlobalBounds().height - 3))) {
			itemsToCraft[i]->setColor(Color(0, 0, 0, 0));
		}
		if (itemsToCraft[i]->getPosition().y >= craftingSelectedSprite.getPosition().y + 10 + (4 * (craftingSelectedSprite.getGlobalBounds().height - 3))) {
			itemsToCraft[i]->setColor(Color(0, 0, 0, 0));
		}
		
		gameWindow.draw(*itemsToCraft[i]);
		
		
	}
	
	
	gameWindow.draw(reqBackground);
	gameWindow.draw(craftingSelectedSprite);
	craftSelect(gameWindow);

	gameWindow.draw(itemsRequired);

	for (auto& el : itemsRequiredToCraft) {
		gameWindow.draw(*el);
	}

	gameWindow.draw(craftedItemQuantity);

	for (auto& el : itemsRequiredToCraftQuantity) {
		gameWindow.draw(*el);
	}
	if (itemsToCraft[craftSelected]->getIsCraftingTableRequired() == true) {
		gameWindow.draw(*craftingTableRequired);
		if (isCraftingTableNear) {
			no_yes.setTextureRect(IntRect(20,0, 20, 20));
		}
		else { no_yes.setTextureRect(IntRect(0, 0, 20, 20)); }
		gameWindow.draw(no_yes);
	}
	if (mouseOnCraft == craftSelected) {
		if (isAbleToCraft()) {
			isAbleToCraftYN.setTextureRect(IntRect(20, 0, 20, 20));
		}
		else { isAbleToCraftYN.setTextureRect(IntRect(0, 0, 20, 20)); }
		gameWindow.draw(isAbleToCraftYN);
	}
}

void Inventory::displayQInventory(RenderWindow& gameWindow)
{
	updateQInventory(gameWindow);
	gameWindow.draw(qInvSprite);
	displayQInventorySelected(gameWindow);
	for (int i = 0; i <= 9; i++) {
		if (inv_vector[i].first != nullptr) {
			gameWindow.draw(*inv_vector[i].first);
		}
	}
	for (int i = 0; i <= 9; i++) {
		gameWindow.draw(itemQuantity[i]);
	}
}

void Inventory::qInvSelect(int selec)
{
	qInvSelected = selec;
}

void Inventory::displayQInventorySelected(RenderWindow& gameWindow)
{
	switch (qInvSelected) {
	case(0): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(1): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) +invSSprite.getLocalBounds().width-1, qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(2): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 2*(invSSprite.getGlobalBounds().width-1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(3): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 3* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(4): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 4* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(5): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 5* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(6): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 6* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(7): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 7* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(8): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 8* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(9): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 9 * (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	}
	gameWindow.draw(invSSprite);
}

void Inventory::displayInventorySelected(RenderWindow& gameWindow)
{
	Vector2f worldPos = gameWindow.mapPixelToCoords(Mouse::getPosition(gameWindow),gameWindow.getView());
	for (int i = 0; i < 44; i++) {
		if (worldPos.x > invSquare[i].left && worldPos.x < (invSquare[i].left + invSquare[i].width) && worldPos.y > invSquare[i].top && worldPos.y < invSquare[i].top + invSquare[i].height) {
			invSSprite.setScale(invSprite.getScale());
			invSSprite.setPosition(invSquare[i].left-2, invSquare[i].top-2);
			gameWindow.draw(invSSprite);
			invSelected = i;
		}

	}
}

bool Inventory::isInventoryFull(int id)
{
	for (auto& el : inv_vector) {
		if (el.first == nullptr || (el.first != nullptr && el.second < el.first->getStackingQuantity() && el.first->getID() == id)) {
			return false;
		}
	}
	return true;
}


int Inventory::getInventorySelected()
{
	return invSelected;
}

IDs Inventory::getQInventorySelectedID()
{
	if (inv_vector[qInvSelected].first != nullptr) {
		return inv_vector[qInvSelected].first->getID();
	}
}

int Inventory::getQInventorySelected()
{
	return qInvSelected;
}

int Inventory::getMouseOnCraft() {
	return mouseOnCraft;
	
}

void Inventory::setCraftSelected(int s, map <IDs, sf::Texture*>& arg1, map <IDs, sf::Texture*>& arg3,map <IDs, Block*>& arg2, map <IDs, Item*>& arg4, Font& gameFont) {
	craftSelected = s;
	itemsRequiredToCraft.clear();
	itemsRequiredToCraftQuantity.clear();
		for (int i = 0; i < itemsToCraft[craftSelected]->getItemsRequiredToCraft().size(); i++) {
			if (itemsToCraft[craftSelected]->getItemsRequiredToCraft()[i].first <= 9) {

				itemsRequiredToCraft.emplace_back(new Block_Item(arg1, arg2, itemsToCraft[craftSelected]->getItemsRequiredToCraft()[i].first, craftingSelectedSprite.getPosition()));
				itemsRequiredToCraftQuantity.emplace_back(new Text);
				itemsRequiredToCraftQuantity[i]->setFont(gameFont);
				itemsRequiredToCraftQuantity[i]->setString(to_string(itemsToCraft[craftSelected]->getItemsRequiredToCraft()[i].second));
				itemsRequiredToCraftQuantity[i]->setCharacterSize(50);
				itemsRequiredToCraftQuantity[i]->setScale(0.4, 0.4);


			}
			if (itemsToCraft[craftSelected]->getItemsRequiredToCraft()[i].first >= 16) {

				itemsRequiredToCraft.emplace_back(new Material_Item(itemsToCraft[craftSelected]->getItemsRequiredToCraft()[i].first,arg3, arg4,craftingSelectedSprite.getPosition()));
				itemsRequiredToCraftQuantity.emplace_back(new Text);
				itemsRequiredToCraftQuantity[i]->setFont(gameFont);
				itemsRequiredToCraftQuantity[i]->setString(to_string(itemsToCraft[craftSelected]->getItemsRequiredToCraft()[i].second));
				itemsRequiredToCraftQuantity[i]->setCharacterSize(50);
				itemsRequiredToCraftQuantity[i]->setScale(0.4, 0.4);


			}
		}
	
}

bool Inventory::isMouseOnCrafitng() {
	return mouseOnCrafting;
}

void Inventory::checkSelectedItem()
{
	if (inv_vector[qInvSelected].first != nullptr and selectedItem != nullptr and getQInventorySelectedID() != selectedItem->getID())
	{
		selectedItem = inv_vector[getQInventorySelected()].first->clone();
	}
	else if (inv_vector[qInvSelected].first != nullptr and selectedItem == nullptr)
	{
		selectedItem = inv_vector[getQInventorySelected()].first->clone();
	}
	else if (inv_vector[qInvSelected].first == nullptr and selectedItem != nullptr)
	{
		selectedItem = nullptr;
	}
}

bool Inventory::isAbleToCraft()
{
	if (mouseOnCraft == craftSelected) {
		for (auto& ite : itemsToCraft[craftSelected]->getItemsRequiredToCraft()) {
			auto i = find_if(inv_vector.begin(), inv_vector.end(), [&ite](auto& it) {if (it.first != nullptr) { return ite.first == it.first->getID() && it.second >= ite.second; } });
			if (i == inv_vector.end() || (itemsToCraft[craftSelected]->getIsCraftingTableRequired() == true && isCraftingTableNear == false)) {
				return false;
			}
		}



		return true;
	}
}

int Inventory::getSelectedToolBlockDamage()
{
	if (inv_vector[qInvSelected].first != nullptr) {
		return inv_vector[qInvSelected].first->getBlockDamage();
	}
	else { return 0; }
}

void Inventory::setIsCraftingTableNear(bool i)
{
	isCraftingTableNear = i;
}


int Inventory::getCraftSelected() {
	return craftSelected;
}
