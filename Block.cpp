#include "Block.h"

Block::Block()
{

}

Block::Block(sf::Texture& _texture, std::vector<int> options, sf::Vector2f pos)
{
    ID = IDs::Grass;
    setTexture(_texture);
    setTextureRect(sf::IntRect(options[0], options[1], options[2], options[3]));
    setPosition(pos);
}

void Block::setBlock(sf::Texture& _texture, std::vector<int> options)
{
    setTexture(_texture);
    setTextureRect(sf::IntRect(options[0], options[1], options[2], options[3]));
}