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
public:
	Player();
	void DestroyBlock(map<int, map<int, B>> &world, RenderWindow& gameWindow);
	void EmplaceBlock(map<int, map<int, B>>& world, RenderWindow& gameWindow, IDs id);
	void Draw(RenderWindow& gameWindow);
	void updateReach();
	IDs getDestroyedBlockID();
	Vector2f getDestroyedBlockPosition();
	bool isBlockDestroyed();
	bool isBlockPlaced();
	void updatePickUpRange();
	FloatRect getPlayerPickUpRange();
	FloatRect* playerReach;
	

};

