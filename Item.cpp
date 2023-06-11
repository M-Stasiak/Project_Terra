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
            setPosition(itemBounds.left + getOrigin().x, argBounds.top - itemBounds.height + getOrigin().y);
        }

        // Top collision
        else if (itemBounds.top > argBounds.top
            and itemBounds.top + itemBounds.height > argBounds.top + argBounds.height
            and itemBounds.left < argBounds.left + argBounds.width
            and itemBounds.left + itemBounds.width > argBounds.left)
        {
            velocity.y = 0;
            setPosition(itemBounds.left + getOrigin().x, argBounds.top + argBounds.height + getOrigin().y);
        }

        // Right collision
        if (itemBounds.left < argBounds.left
            and itemBounds.left + itemBounds.width < argBounds.left + argBounds.width
            and itemBounds.top < argBounds.top + argBounds.height
            and itemBounds.top + itemBounds.height > argBounds.top)
        {
            velocity.x = 0;
            setPosition(argBounds.left - itemBounds.width + getOrigin().x, itemBounds.top + getOrigin().y);
        }

        // Left collision
        else if (itemBounds.left > argBounds.left
            and itemBounds.left + itemBounds.width > argBounds.left + argBounds.width
            and itemBounds.top < argBounds.top + argBounds.height
            and itemBounds.top + itemBounds.height > argBounds.top)
        {
            velocity.x = 0;
            setPosition(argBounds.left + argBounds.width + getOrigin().x, itemBounds.top + getOrigin().y);
        }
    }
}

void Item::goToPlayer(Vector2f playerPosition)
{
    velocity.x = (playerPosition.x - getPosition().x)/5;
    velocity.y = (playerPosition.y - getPosition().y)/5;
    move(velocity);
}

vector<pair<IDs, int>> Item::getItemsRequiredToCraft()
{
    return itmsRequiredToCraft;
}

int Item::getCraftedQuantity()
{
    return craftedQuantity;
}

int Item::getBlockDamage()
{
    return blockDamage;
}

void Item::GravityUpdate(float elapsed, float gravity)
{
    if (velocity.y < 6)
    {
        velocity.y += gravity * elapsed;
    }
    move(velocity);
}

int Item::getStackingQuantity()
{
    return stackingQuantity;
}

bool Item::getIsCraftingTableRequired() {
    return isCraftingTableRequired;
}