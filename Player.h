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
public:
	Player();
	void DestroyBlock(map<int, map<int, B>> &world, RenderWindow& gameWindow);
	void Draw(RenderWindow& gameWindow);
	void updateReach();
	IDs getDestroyedBlockID();
	Vector2f getDestroyedBlockPosition();
	bool isBlockDestroyed();
	void updatePickUpRange();
	FloatRect getPlayerPickUpRange();
	FloatRect* playerReach;
	

};

