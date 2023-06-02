#include "Item.h"

Item::Item() {
    velocity.x = 0;
    velocity.y = 0;
}
void Item::CheckCollisions(const sf::FloatRect* arg)
{
    FloatRect itemBounds = getGlobalBounds();
    FloatRect argBounds = *arg;
    nextPosition = itemBounds;
    nextPosition.left += velocity.x;
    nextPosition.top += velocity.y;

    if (argBounds.intersects(nextPosition))
    {
        // Bottom collision
        if (itemBounds.top < argBounds.top
            and itemBounds.top + itemBounds.height < argBounds.top + argBounds.height
            and itemBounds.left < argBounds.left + argBounds.width
            and itemBounds.left + itemBounds.width > argBounds.left)
        {
            velocity.y = 0;
            setPosition(itemBounds.left + origin.x, argBounds.top - itemBounds.height + origin.y);
        }

        // Top collision
        else if (itemBounds.top > argBounds.top
            and itemBounds.top + itemBounds.height > argBounds.top + argBounds.height
            and itemBounds.left < argBounds.left + argBounds.width
            and itemBounds.left + itemBounds.width > argBounds.left)
        {
            velocity.y = 0;
            setPosition(itemBounds.left + origin.x, argBounds.top + argBounds.height + origin.y);
        }

        // Right collision
        if (itemBounds.left < argBounds.left
            and itemBounds.left + itemBounds.width < argBounds.left + argBounds.width
            and itemBounds.top < argBounds.top + argBounds.height
            and itemBounds.top + itemBounds.height > argBounds.top)
        {
            velocity.x = 0;
            setPosition(argBounds.left - itemBounds.width + origin.x, itemBounds.top + origin.y);
        }

        // Left collision
        else if (itemBounds.left > argBounds.left
            and itemBounds.left + itemBounds.width > argBounds.left + argBounds.width
            and itemBounds.top < argBounds.top + argBounds.height
            and itemBounds.top + itemBounds.height > argBounds.top)
        {
            velocity.x = 0;
            setPosition(argBounds.left + argBounds.width + origin.x, itemBounds.top + origin.y);
        }
    }
}

void Item::goToPlayer(Vector2f playerPosition)
{
    velocity.x = (playerPosition.x - getPosition().x)/5;
    velocity.y = (playerPosition.y - getPosition().y)/5;
    move(velocity);
}

void Item::GravityUpdate(float elapsed, float gravity)
{
   
    velocity.y += gravity * elapsed;
    move(velocity);
}

int Item::getStackingQuantity()
{
    return stackingQuantity;
}