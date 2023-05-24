#include "Player.h"



Player::Player()
{
	blockDestroyed = false;
	Texture entityTexture;
	entityTexture.loadFromFile("Textures/adventurer.png");
	setEntity(entityTexture, { {4, 0, 0, 50, 37}, {6, 50, 37, 50, 37} });
	origin.x = 25; origin.y = 18.5;
	setOrigin(origin);
	playerReach = new FloatRect(0, 0, 100, 100);
}

void Player::DestroyBlock(map<int, map<int, B>> &world, RenderWindow& gameWindow)
{
	Vector2f worldPos = gameWindow.mapPixelToCoords(Mouse::getPosition(gameWindow), gameWindow.getView());
	if (worldPos.x > playerReach->left && worldPos.x < (playerReach->left + playerReach->width) && worldPos.y > playerReach->top && worldPos.y < playerReach->top + playerReach->height) {
		if (world[worldPos.x / 16][worldPos.y / 16].ID != IDs::AirID) {
			sf::FloatRect p((int)worldPos.x, (int)worldPos.y, 0, 0);
			B a(IDs::AirID, p);
			destroyedBlockID = world[worldPos.x / 16][worldPos.y / 16].ID;
			destroyedBlockPosition.x = world[worldPos.x / 16][worldPos.y / 16].rect.left;
			destroyedBlockPosition.y = world[worldPos.x / 16][worldPos.y / 16].rect.top;
			world[worldPos.x / 16][worldPos.y / 16] = a;
			blockDestroyed = true;
		}
	}
}


void Player::Draw(RenderWindow &gameWindow)
{
	gameWindow.draw(*this);
}

void Player::updateReach()
{
	blockDestroyed = false;
	playerReach->left = getPosition().x - (playerReach->width / 2);
	playerReach->top = getPosition().y - (playerReach->height / 2);
	cout << playerReach->left << " " << playerReach->top << endl;
	cout << getPosition().x << " " << getPosition().y << endl;

}

IDs Player::getDestroyedBlockID()
{
	return destroyedBlockID;
}

Vector2f Player::getDestroyedBlockPosition()
{
	return destroyedBlockPosition;
}

bool Player::isBlockDestroyed()
{
	return blockDestroyed;
}
