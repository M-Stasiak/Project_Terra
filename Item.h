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
    sf::FloatRect nextPosition;
    Vector2f origin;
    sf::Vector2f velocity;

protected:
    

public:
    Item();
    virtual void nothing() = 0;
    void GravityUpdate(float elapsed, float gravity);
    void CheckCollisions(const sf::FloatRect* arg);
    void goToPlayer(Vector2f playerPosition);
    virtual int getID()=0;

};

