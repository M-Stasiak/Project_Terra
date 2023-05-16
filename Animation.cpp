#include "Animation.h"

Animation::Animation(sf::Texture _texture, std::vector<int> options)
{
    nFrames = options[0];
    texture = _texture;
    for (int i = 0; i < nFrames; i++)
    {
        frames.push_back({ options[1] + i*options[3], options[2], options[3], options[4] });
    }
}

void Animation::ApplyToSprite(sf::Sprite *s)
{
    s->setTexture(texture);
    s->setTextureRect(frames[iFrame]);
}

void Animation::Update(float elapsed)
{
    time += elapsed;
    if (time >= holdTime)
    {
        time = 0;
        ChangeFrame();
    }
}

void Animation::ChangeFrame()
{
    if (++iFrame >= nFrames) iFrame = 0;

}