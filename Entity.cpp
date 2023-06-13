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
    healthBar.setHealthBar(health, maxHealth);

    animations[AnimationName::Idle] = new Animation(texture, options[0], options.size() > 2 ? options[2] : vector<int>{ 0,0,0,0 });
    animations[AnimationName::Walk] = new Animation(texture, options[1], options.size() > 2 ? options[2] : vector<int>{ 0,0,0,0 });
}

void Entity::setEntity(sf::Texture _texture, std::vector<std::vector<int>> options)
{
    texture = _texture;
    setTexture(texture);
    healthBar.setHealthBar(health, maxHealth);

    animations[AnimationName::Idle] = new Animation(texture, options[0], options.size() > 2 ? options[2] : vector<int>{ 0,0,0,0 });
    animations[AnimationName::Walk] = new Animation(texture, options[1], options.size() > 2 ? options[2] : vector<int>{ 0,0,0,0 });
}

void Entity::Up(float elapsed) { if (!jumping) { jumping = true; jumpVelocity = -jumpSpeed; } }
void Entity::Down(float elapsed) { velocity.y += speed * elapsed; }
void Entity::Left(float elapsed) { setScale({ (float)(-1)*abs(getScale().x), getScale().y }); velocity.x += -speed * elapsed; }
void Entity::Right(float elapsed) { setScale({ (float)abs(getScale().x), getScale().y }); velocity.x += speed * elapsed; }
void Entity::Attack(float elapsed, Entity& entity)
{
    attackTime += elapsed;
    if (attackTime > holdAttackTime)
    {
        state = AnimationName::Attack;
        entity.setState(AnimationName::Damage);
        entity.TakeDamage(10);
        attackTime = 0;
    }
}

void Entity::TakeDamage(int damage)
{
    health -= damage;
    if (health <= 0) setState(AnimationName::Death);
}

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
    if (jumpVelocity < 300) jumpVelocity += gravity;
    velocity.y += jumpVelocity * elapsed;
}

void Entity::Update(float elapsed)
{
    if (isPlayer) cout << state << endl;
    if (isAlive)
    {
        if (state == AnimationName::Basic)
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
        }
        else
        {
            if (animations[state] != nullptr)
            {
                animations[state]->Update(elapsed);
                animations[state]->ApplyToSprite(this);

                if (animations[state]->isEnded())
                {
                    if (state == AnimationName::Death)
                    {
                        isAlive = false;
                        animations[state]->LastFrame();
                        animations[state]->ApplyToSprite(this);
                    }
                    else state = AnimationName::Basic;
                }
            }
            else state = AnimationName::Basic;
        }
    }
    else isDeadTime += elapsed;

    velocity = sf::Vector2f(0, 0);
    setEntityView();
}

View Entity::getEntityView()
{
    return entityView;
}

void Entity::Respawn()
{
    isAlive = true;
    health = maxHealth;
    state = AnimationName::Basic;
    isDeadTime = 0;
}


