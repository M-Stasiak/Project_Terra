#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Block.h";
#include <iostream>

using namespace sf;
using namespace std;

enum item_type {
    block,
    tool
};

class Item : public Sprite
{
private:
    item_type type;

public:
    Item();
    virtual void nothing() = 0;
    virtual int getID()=0;
    virtual int getStackingQuantity() = 0;

};

class I
{
public:
    IDs ID;
    sf::FloatRect rect;
    sf::Vector2f velocity;
    I() {}
    I(IDs id, sf::FloatRect r)
    {
        ID = id;
        rect = r;
    }

};

void CheckCollisions(I& item, const sf::FloatRect* arg);
void GravityUpdate(I& item, float elapsed, float gravity);
void goToPlayer(I& item, Vector2f playerPosition);

