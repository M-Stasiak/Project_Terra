#include "Entity.h"

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

void Entity::Up(float elapsed) { move(sf::Vector2f(0, -velocity * elapsed)); }
void Entity::Down(float elapsed) { move(sf::Vector2f(0, velocity * elapsed)); }
void Entity::Left(float elapsed) { setScale({ (float)(-1)*abs(getScale().x), getScale().y }); move(sf::Vector2f(-velocity * elapsed, 0)); }
void Entity::Right(float elapsed) { setScale({ (float)abs(getScale().x), getScale().y }); move(sf::Vector2f(velocity * elapsed, 0)); }

void Entity::Update(float elapsed)
{
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
}