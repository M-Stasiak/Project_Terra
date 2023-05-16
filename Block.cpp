#include "Block.h"

Block::Block()
{

}

Block::Block(sf::Texture _texture, std::vector<int> options, sf::Vector2f pos)
{
    ID = IDs::Grass;
    texture = _texture;
    setTexture(texture);
    setTextureRect(sf::IntRect(options[0], options[1], options[2], options[3]));
    setPosition(pos);
}

void Block::setBlock(sf::Texture _texture, std::vector<int> options)
{
    texture = _texture;
    setTexture(texture);
    setTextureRect(sf::IntRect(options[0], options[1], options[2], options[3]));
}