#include "Inventory.h"


void Inventory::initFont(Font& gameFont)
{
	for (int i = 0; i < 40; i++) {
		itemQuantity[i].setFont(gameFont);
	}
	mouseItemQuantity.setFont(gameFont);
	craftingItemQuantity.setFont(gameFont);
}

void Inventory::initTextures()
{
	if (!invTexture.loadFromFile("Textures/inventory.png")) { cout << "No texture found" << endl; }
	if (!qInvTexture.loadFromFile("Textures/qInventory.png")) { cout << "No texture found" << endl; }
	if (!invSTexture.loadFromFile("Textures/inventorySelect.png")) { cout << "No texture found" << endl; }
	if (!craftingSlotTexture.loadFromFile("Textures/Inventory_Slot.png")) { cout << "No texture found" << endl; }
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
}



void Inventory::updateInventory(RenderWindow& gameWindow)
{

	mouseOnCrafting = false;
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


void Inventory::initInventory(map <IDs, sf::Texture*>& arg1, map <IDs, Block*>& arg2)
{
	for (int i = 1; i <= 44;i++) {
		inv_vector.emplace_back(nullptr, 0);

	}
	mouseItem.first = nullptr;
	mouseItem.second = 0;

	itemsToCraft.emplace_back(new Block_Item(arg1,arg2,IDs::GrassID,craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::DirtID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::RockID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::WoodID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::PlankID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::LeavesID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::CactusID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::SandID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::ChestID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::RockID, craftingSelectedSprite.getPosition()));
	itemsToCraft.emplace_back(new Block_Item(arg1, arg2, IDs::ChestID, craftingSelectedSprite.getPosition()));

	for (int i = 0; i < itemsToCraft.size(); i++) {
		slotSprites.emplace_back(new Sprite);
		slotSprites[i]->setTexture(craftingSlotTexture);
	}
}

void Inventory::craftSelect(RenderWindow& gameWindow)
{
	Vector2f worldPos = gameWindow.mapPixelToCoords(Mouse::getPosition(gameWindow), gameWindow.getView());
	for (int i = 0; i <itemsToCraft.size(); i++) {
		if (worldPos.x > itemsToCraft[i]->getGlobalBounds().left && worldPos.x < (itemsToCraft[i]->getGlobalBounds().left + itemsToCraft[i]->getGlobalBounds().width) && worldPos.y > itemsToCraft[i]->getGlobalBounds().top && worldPos.y < itemsToCraft[i]->getGlobalBounds().top + itemsToCraft[i]->getGlobalBounds().height) {
			mouseOnCraft = i;
			mouseOnCrafting = true;
		}

	}
}

Inventory::Inventory(RenderWindow& gameWindow, Font& gameFont, map <IDs, sf::Texture*>& arg1, map <IDs, Block*>& arg2)
{
	qInvSelected = 0;
	craftSelected = 0;
	initFont(gameFont);
	initTextures();
	initSprites(gameWindow);
	initInventory(arg1,arg2);
}

void Inventory::displayInventory(RenderWindow& gameWindow, map <IDs, sf::Texture*>& arg)
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
	
	

	gameWindow.draw(craftingSelectedSprite);
	craftSelect(gameWindow);

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

void Inventory::setCraftSelected(int s) {
	craftSelected = s;
}

bool Inventory::isMouseOnCrafitng() {
	return mouseOnCrafting;
}