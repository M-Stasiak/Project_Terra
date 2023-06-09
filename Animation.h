#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Animation
{
private:
    float holdTime = 0.1f; float time = 0;
    int iFrame = 0, nFrames = 0;
    bool isEnd = false;
    sf::Texture texture;
    std::vector<sf::IntRect> frames;

    void ChangeFrame();

public:
    Animation(sf::Texture _texture, std::vector<int> options, std::vector<int> extraOptions = {0,0,0,0});
    void ApplyToSprite(sf::Sprite* s);
    void Update(float elapsed);
    void LastFrame();
    bool isEnded();
};

