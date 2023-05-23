#include "Entity.h"

void Entity::setEntityView()
{
    entityView.setCenter(lastPosition.x+10, lastPosition.y+10);
    entityView.setSize(int((VideoMode::getDesktopMode().width) * 0.5), int((VideoMode::getDesktopMode().height) * 0.5));
}

Entity::Entity()
{

}

Entity::Entity(sf::Texture _texture, std::vector<std::vector<int>> options)
{
    texture = _texture;
    setTexture(texture);

    animations[AnimationName::Idle] = new Animation(texture, options[0]);
    animations[AnimationName::Walk] = new Animation(texture, options[1]);
}

void Entity::setEntity(sf::Texture _texture, std::vector<std::vector<int>> options)
{
    texture = _texture;
    setTexture(texture);

    animations[AnimationName::Idle] = new Animation(texture, options[0]);
    animations[AnimationName::Walk] = new Animation(texture, options[1]);
}

void Entity::Up(float elapsed) { if (!jumping) { jumping = true; jumpVelocity = -jumpSpeed; } }
void Entity::Down(float elapsed) { velocity.y += speed * elapsed; }
void Entity::Left(float elapsed) { setScale({ (float)(-1)*abs(getScale().x), getScale().y }); velocity.x += -speed * elapsed; }
void Entity::Right(float elapsed) { setScale({ (float)abs(getScale().x), getScale().y }); velocity.x += speed * elapsed; }

void Entity::CheckCollisions(const sf::FloatRect *arg)
{
    FloatRect playerBounds = getGlobalBounds();
    FloatRect argBounds = *arg;
    nextPosition = playerBounds;
    nextPosition.left += velocity.x;
    nextPosition.top += velocity.y;

    if (argBounds.intersects(nextPosition))
    {
        // Bottom collision
        if (playerBounds.top < argBounds.top
            and playerBounds.top + playerBounds.height < argBounds.top + argBounds.height
            and playerBounds.left < argBounds.left + argBounds.width
            and playerBounds.left + playerBounds.width > argBounds.left)
        {
            velocity.y = 0;
            setPosition(playerBounds.left + origin.x, argBounds.top - playerBounds.height + origin.y);
            jumping = false;
        }

        // Top collision
        else if (playerBounds.top > argBounds.top
            and playerBounds.top + playerBounds.height > argBounds.top + argBounds.height
            and playerBounds.left < argBounds.left + argBounds.width
            and playerBounds.left + playerBounds.width > argBounds.left)
        {
            velocity.y = 0;
            setPosition(playerBounds.left + origin.x, argBounds.top + argBounds.height + origin.y);
        }

        // Right collision
        if (playerBounds.left < argBounds.left
            and playerBounds.left + playerBounds.width < argBounds.left + argBounds.width
            and playerBounds.top < argBounds.top + argBounds.height
            and playerBounds.top + playerBounds.height > argBounds.top)
        {
            velocity.x = 0;
            setPosition(argBounds.left - playerBounds.width + origin.x, playerBounds.top + origin.y);
        }

        // Left collision
        else if (playerBounds.left > argBounds.left
            and playerBounds.left + playerBounds.width > argBounds.left + argBounds.width
            and playerBounds.top < argBounds.top + argBounds.height
            and playerBounds.top + playerBounds.height > argBounds.top)
        {
            velocity.x = 0;
            setPosition(argBounds.left + argBounds.width + origin.x, playerBounds.top + origin.y);
        }
    }
}

void Entity::GravityUpdate(float elapsed, float gravity)
{
    if (jumpVelocity < 200) jumpVelocity += gravity;
    velocity.y += jumpVelocity * elapsed;
}

void Entity::Update(float elapsed)
{
    move(velocity);
    if (getPosition() != lastPosition)
    {
        animations[AnimationName::Walk]->Update(elapsed);
        animations[AnimationName::Walk]->ApplyToSprite(this);
    }
    else
    {
        animations[AnimationName::Idle]->Update(elapsed);
        animations[AnimationName::Idle]->ApplyToSprite(this);
    }
    lastPosition = getPosition();

    velocity = sf::Vector2f(0, 0);
    setEntityView();
}

View Entity::getEntityView()
{
    return entityView;
}


