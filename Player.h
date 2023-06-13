#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Entity.h"
#include "Block.h"


class Player : public Entity
{
private:
	int x;
	
	FloatRect* playerPickUpRange;
	IDs destroyedBlockID;
	Vector2f destroyedBlockPosition;
	bool blockDestroyed;
	bool blockPlaced;
	bool chestOpened;
	int blockDamage;
	Vector2f placedBlockPosition;
	Vector2f openedChestPosition;
public:
	Player();
	void DestroyBlock(map<int, map<int, B>> &world, RenderWindow& gameWindow,int dmg);
	void EmplaceBlock(map<int, map<int, B>>& world, RenderWindow& gameWindow, IDs id);
	void UseBlock(RenderWindow& gameWindow, map<int, map<int, B>>& world);
	void Draw(RenderWindow& gameWindow);
	void updateReach();
	IDs getDestroyedBlockID();
	Vector2f getDestroyedBlockPosition();
	bool isBlockDestroyed();
	bool isBlockPlaced();
	void updatePickUpRange();
	bool isChestOpened();
	void setChestOpened(bool i);
	FloatRect getPlayerPickUpRange();
	FloatRect* playerReach;
	Vector2f getPlacedBlockPosition();
	Vector2f getOpenedChestPosition();
	

};

