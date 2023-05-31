#include "Player.h"



Player::Player()
{
	blockDestroyed = false;
	Texture entityTexture;
	entityTexture.loadFromFile("Textures/Entities/CharacterSpriteSheet.png");
	setEntity(entityTexture, { {8, 1344, 0, 64, 64}, {8, 5824, 0, 64, 64}, {16, 16, -32, -32} });
	origin.x = 16; origin.y = 16;
	setOrigin(origin);
	playerReach = new FloatRect(0, 0, 150, 150);
	playerPickUpRange = new FloatRect(0, 0, 100, 100);
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
	playerReach->left = getPosition().x - float(playerReach->width / 2) ;
	playerReach->top = getPosition().y - float(playerReach->height / 2) ;

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

void Player::updatePickUpRange()
{
	playerPickUpRange->left = getPosition().x - playerPickUpRange->width/2;
	playerPickUpRange->top = getPosition().y - playerPickUpRange->height / 2;
}

FloatRect Player::getPlayerPickUpRange()
{
	return *playerPickUpRange;
}
