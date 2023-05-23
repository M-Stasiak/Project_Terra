#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Animation.h"

enum AnimationName
{
    Idle = 0,
    Walk = 1
};

class Entity : public sf::Sprite
{
private:
    float speed = 100;
    float jumpSpeed = 400;
    float jumpVelocity = 0;
    bool jumping = false;
    sf::Vector2f lastPosition;
    sf::Vector2f velocity;
    sf::FloatRect nextPosition;
    View entityView;
    sf::Texture texture;
    std::map<AnimationName, Animation*> animations;
    void setEntityView();

protected:
    Vector2f origin;

public:
    Entity();
    Entity(sf::Texture _texture, std::vector<std::vector<int>> options);
    void setEntity(sf::Texture _texture, std::vector<std::vector<int>> options);
    void Up(float elapsed);
    void Down(float elapsed);
    void Left(float elapsed);
    void Right(float elapsed);
    void Update(float elapsed);
    View getEntityView();
    

    void GravityUpdate(float elapsed, float gravity);
    void CheckCollisions(const sf::FloatRect *arg);

    virtual void Draw(RenderWindow&) = 0;
};

