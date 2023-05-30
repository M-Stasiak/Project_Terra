#include "Item.h"

Item::Item() 
{

}
void CheckCollisions(I& item, const sf::FloatRect* arg)
{
    FloatRect itemBounds = item.rect;
    FloatRect argBounds = *arg;
    sf::FloatRect nextPosition = itemBounds;
    nextPosition.left += item.velocity.x;
    nextPosition.top += item.velocity.y;

    if (argBounds.intersects(nextPosition))
    {
        // Bottom collision
        if (itemBounds.top < argBounds.top
            and itemBounds.top + itemBounds.height < argBounds.top + argBounds.height
            and itemBounds.left < argBounds.left + argBounds.width
            and itemBounds.left + itemBounds.width > argBounds.left)
        {
            item.velocity.y = 0;
            item.rect.left = itemBounds.left;
            item.rect.top = argBounds.top - itemBounds.height;
        }

        // Top collision
        else if (itemBounds.top > argBounds.top
            and itemBounds.top + itemBounds.height > argBounds.top + argBounds.height
            and itemBounds.left < argBounds.left + argBounds.width
            and itemBounds.left + itemBounds.width > argBounds.left)
        {
            item.velocity.y = 0;
            item.rect.left = itemBounds.left;
            item.rect.top = argBounds.top + argBounds.height;
        }

        // Right collision
        if (itemBounds.left < argBounds.left
            and itemBounds.left + itemBounds.width < argBounds.left + argBounds.width
            and itemBounds.top < argBounds.top + argBounds.height
            and itemBounds.top + itemBounds.height > argBounds.top)
        {
            item.velocity.x = 0;
            item.rect.left = argBounds.left - itemBounds.width;
            item.rect.top = itemBounds.top;
        }

        // Left collision
        else if (itemBounds.left > argBounds.left
            and itemBounds.left + itemBounds.width > argBounds.left + argBounds.width
            and itemBounds.top < argBounds.top + argBounds.height
            and itemBounds.top + itemBounds.height > argBounds.top)
        {
            item.velocity.x = 0;
            item.rect.left = argBounds.left + argBounds.width;
            item.rect.top = itemBounds.top;
        }
    }
}

void GravityUpdate(I& item, float elapsed, float gravity)
{
    item.velocity.y += gravity * elapsed;
    item.rect.top += item.velocity.y;
}

void goToPlayer(I& item, Vector2f playerPosition)
{
    item.velocity.x = (playerPosition.x - item.rect.left) / 5;
    item.velocity.y = (playerPosition.y - item.rect.top) / 5;
    item.rect.left += item.velocity.x;
    item.rect.top += item.velocity.y;
}