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
	invSprite.setScale(2, 2);
	qInvSprite.setTexture(qInvTexture);
	qInvSprite.setScale(1, 1);
	invSSprite.setTexture(invSTexture);
	invSSprite.setScale(invSprite.getScale());
}



void Inventory::updateInventory(RenderWindow& gameWindow)
{

	invSprite.setPosition(gameWindow.getView().getCenter().x - (invSprite.getScale().x * 101.f), gameWindow.getView().getCenter().y - (invSprite.getScale().x * 68.f));
	invSquare[0].top = invSprite.getPosition().y + 12 + 2;
	invSquare[0].left = invSprite.getPosition().x + 12 + 2;
	invSquare[1].top = invSprite.getPosition().y + 12 + invSquare[0].height + 4;
	invSquare[1].left = invSprite.getPosition().x + 12 + 2;
	invSquare[2].top = invSprite.getPosition().y + 12 + 2;
	invSquare[2].left = invSprite.getPosition().x + 12 + 2 + 96;
	invSquare[3].top = invSprite.getPosition().y + 12 + invSquare[0].height + 4;
	invSquare[3].left = invSprite.getPosition().x + 12 + 2 + 96;

	invSquare[4].top = invSprite.getPosition().y + 12 + (invSquare[0].height + 4) * 5 + 10;
	invSquare[4].left = invSprite.getPosition().x + 12 + 2;
	for (int i = 5; i <= 13; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + (invSquare[0].height + 4) * 5 + 10;
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
    }
	invSquare[14].top = invSprite.getPosition().y + 12 + 2;
	invSquare[14].left = invSprite.getPosition().x + 12 + 2 + 96+invSquare[14].width+20;
	for (int i = 15; i <= 19; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + 2;
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
	}
	invSquare[20].top = invSprite.getPosition().y + 12 + 2 + invSquare[14].height+2;
	invSquare[20].left = invSprite.getPosition().x + 12 + 2 + 96 + invSquare[14].width + 20;
	for (int i = 21; i <= 25; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + 2 + invSquare[14].height+2;
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
	}
	invSquare[26].top = invSprite.getPosition().y + 12 + 2 + 2*(invSquare[14].height + 2);
	invSquare[26].left = invSprite.getPosition().x + 12 + 2 + 96 + invSquare[14].width + 20;
	for (int i = 27; i <= 31; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + 2 + 2*(invSquare[14].height + 2);
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
	}
	invSquare[32].top = invSprite.getPosition().y + 12 + 2 + 3 * (invSquare[14].height + 2);
	invSquare[32].left = invSprite.getPosition().x + 12 + 2 + 96 + invSquare[14].width + 20;
	for (int i = 33; i <= 37; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + 2 + 3 * (invSquare[14].height + 2);
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
	}
	invSquare[38].top = invSprite.getPosition().y + 12 + 2 + 4 * (invSquare[14].height + 2);
	invSquare[38].left = invSprite.getPosition().x + 12 + 2 + 96 + invSquare[14].width + 20;
	for (int i = 39; i <= 43; i++) {
		invSquare[i].top = invSprite.getPosition().y + 12 + 2 + 4 * (invSquare[14].height + 2);
		invSquare[i].left = (invSquare[i - 1].left + invSquare[i].width + 2);
	}


	
}

void Inventory::updateQInventory(RenderWindow& gameWindow)
{
	invSSprite.setScale(qInvSprite.getScale());
	qInvSprite.setPosition(gameWindow.getView().getCenter().x - (invSprite.getScale().x * 203.f*0.95f), gameWindow.getView().getCenter().y - (invSprite.getScale().x * 32.f * 3.25));
}

Inventory::Inventory(RenderWindow& gameWindow)
{
	selected = 1;
	initTextures();
	initSprites(gameWindow);
	initSquares();
}

void Inventory::displayInventory(RenderWindow& gameWindow)
{
	updateInventory(gameWindow);
	gameWindow.draw(invSprite);
	
}

void Inventory::displayQInventory(RenderWindow& gameWindow)
{
	updateQInventory(gameWindow);
	gameWindow.draw(qInvSprite);
}

void Inventory::qInvSelect(int selec)
{
	selected = selec;
}

void Inventory::displayQInventorySelected(RenderWindow& gameWindow)
{
	switch (selected) {
	case(1): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(2): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) +invSSprite.getLocalBounds().width-1, qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(3): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 2*(invSSprite.getGlobalBounds().width-1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(4): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 3* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(5): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 4* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(6): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 5* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(7): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 6* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(8): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 7* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(9): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 8* (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	case(0): {invSSprite.setPosition(qInvSprite.getPosition().x + (6 * qInvSprite.getScale().x) + 9 * (invSSprite.getGlobalBounds().width - 1), qInvSprite.getPosition().y + (6 * qInvSprite.getScale().y)); break; }
	}
	gameWindow.draw(invSSprite);
}

void Inventory::displayInventorySelected(RenderWindow& gameWindow)
{
	Vector2f worldPos = gameWindow.mapPixelToCoords(Mouse::getPosition(gameWindow),gameWindow.getView());
	cout << worldPos.x << endl;
	for (int i = 0; i < 44; i++) {
		if (worldPos.x > invSquare[i].left && worldPos.x < (invSquare[i].left + invSquare[i].width) && worldPos.y > invSquare[i].top && worldPos.y < invSquare[i].top + invSquare[i].height) {
			invSSprite.setScale(invSprite.getScale());
			invSSprite.setPosition(invSquare[i].left-2, invSquare[i].top-2);
			gameWindow.draw(invSSprite);
		}

	}
}

void Inventory::initSquares()
{
	for (int i = 0; i < 44; i++) {
		invSquare[i].width = invSSprite.getGlobalBounds().width-4;
		invSquare[i].height = invSSprite.getGlobalBounds().height-4;
	}


}