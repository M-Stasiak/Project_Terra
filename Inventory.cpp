#include "Inventory.h"

void Inventory::initTextures()
{
	if (!invTexture.loadFromFile("Textures/inventory.png")) { cout << "No texture found" << endl; }
	if (!qInvTexture.loadFromFile("Textures/qInventory.png")) { cout << "No texture found" << endl; }
	if (!invSTexture.loadFromFile("Textures/inventorySelect.png")) { cout << "No texture found" << endl; }
}

void Inventory::initSprites(RenderWindow& gameWindow)
{
	invSprite.setTexture(invTexture);
	qInvSprite.setTexture(qInvTexture);
	invSSprite.setTexture(invSTexture);
	invSSprite.setPosition(qInvSprite.getPosition().x+6, qInvSprite.getPosition().y+6);
}

void Inventory::updateInventory()
{
}

void Inventory::updateQInventory()
{
}

Inventory::Inventory(RenderWindow& gameWindow)
{
	initTextures();
	initSprites(gameWindow);
}

void Inventory::displayInventory(RenderWindow& gameWindow)
{
	gameWindow.draw(invSprite);
}

void Inventory::displayQInventory(RenderWindow& gameWindow)
{
	gameWindow.draw(qInvSprite);
}

void Inventory::qInvSelect(int selec)
{
	selected = selec;
}

void Inventory::displayQInventorySelected(RenderWindow& gameWindow)
{
	switch (selected) {
	case(1): {invSSprite.setPosition(qInvSprite.getPosition().x + 6, qInvSprite.getPosition().y + 6); break; }
	case(2): {invSSprite.setPosition(qInvSprite.getPosition().x + 6 +invSSprite.getLocalBounds().width-1, qInvSprite.getPosition().y + 6); break; }
	case(3): {invSSprite.setPosition(qInvSprite.getPosition().x + 6 + 2*(invSSprite.getGlobalBounds().width-1), qInvSprite.getPosition().y + 6); break; }
	case(4): {invSSprite.setPosition(qInvSprite.getPosition().x + 6 + 3* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + 6); break; }
	case(5): {invSSprite.setPosition(qInvSprite.getPosition().x + 6 + 4* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + 6); break; }
	case(6): {invSSprite.setPosition(qInvSprite.getPosition().x + 6 + 5* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + 6); break; }
	case(7): {invSSprite.setPosition(qInvSprite.getPosition().x + 6 + 6* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + 6); break; }
	case(8): {invSSprite.setPosition(qInvSprite.getPosition().x + 6 + 7* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + 6); break; }
	case(9): {invSSprite.setPosition(qInvSprite.getPosition().x + 6 + 8* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + 6); break; }
	case(0): {invSSprite.setPosition(qInvSprite.getPosition().x + 6 + 9 * (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + 6); break; }
	}
	gameWindow.draw(invSSprite);
}
