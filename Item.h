#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Block.h";

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
    Item() {};

    virtual void nothing() = 0;

};

