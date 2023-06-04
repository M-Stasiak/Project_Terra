#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Block.h";
#include "Entity.h"
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
    sf::FloatRect nextPosition;
    sf::Vector2f velocity;

protected:
    IDs ID;
    Vector2f origin;
    int stackingQuantity;
    bool isUsing = false;
    item_type type;
    vector<pair<IDs, int>> itmsRequiredToCraft;
    int craftedQuantity;


public:
  

    Item();
    virtual void nothing() = 0;
    void GravityUpdate(float elapsed, float gravity);
    void CheckCollisions(const sf::FloatRect* arg);
    void goToPlayer(Vector2f playerPosition);
    int getStackingQuantity();
    Vector2f getSpecialOrigin() { return origin; };
    IDs getID() { return ID; };
    item_type getItemType() { return type; };
    virtual void Update(float elapsed, Entity& entity, vector<Entity*>& entities) = 0;
    virtual void Use() = 0;
    virtual unique_ptr<Item> clone() const = 0;
    vector<pair<IDs, int>> getItemsRequiredToCraft();
    int getCraftedQuantity();


};

