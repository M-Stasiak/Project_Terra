#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Animation.h"
#include "HealthBar.h"
#include "Block.h"

enum AnimationName
{
    Basic,
    Idle,
    Walk,
    Attack,
    Damage,
    Death
};

class Entity : public sf::Sprite
{
private:
    float jumpVelocity = 0;
    bool jumping = false;
    sf::Vector2f lastPosition;
    sf::Vector2f velocity;
    sf::FloatRect nextPosition;
    View entityView;
    sf::Texture texture;
    void setEntityView();

protected:
    bool isAlive = true, isPlayer = false;
    float isDeadTime = 0, healingTime = 0;
    int health = 100, maxHealth = 100;
    float speed = 200;
    float jumpSpeed = 400;
    float attackTime, holdAttackTime = 2;
    AnimationName state = AnimationName::Basic;
    Vector2f origin;
    HealthBar healthBar;
    std::map<AnimationName, Animation*> animations;

public:
    Entity();
    Entity(sf::Texture _texture, std::vector<std::vector<int>> options);
    void setEntity(sf::Texture _texture, std::vector<std::vector<int>> options);
    void Up(float elapsed);
    void Down(float elapsed);
    void Left(float elapsed);
    void Right(float elapsed);
    void TakeDamage(int damage);
    virtual void Attack(float elapsed, Entity& entity);
    virtual void Update(float elapsed);
    virtual void UpdateAI(float elapsed, Entity& player, map<int, map<int, B>>& world) {};
    View getEntityView();
    

    void GravityUpdate(float elapsed, float gravity);
    void CheckCollisions(const sf::FloatRect *arg);
    void setState(AnimationName _state) { state = _state; };
    AnimationName getState() { return state; };
    void Respawn();
    void Heal(int arg) { if (health + arg < maxHealth) health += arg; else health = maxHealth; };
    bool getIsAlive() { return isAlive; };
    bool getIsPlayer() { return isPlayer; };
    float getIsDeadTime() { return isDeadTime; };

    virtual void Draw(RenderWindow&) = 0;
};

