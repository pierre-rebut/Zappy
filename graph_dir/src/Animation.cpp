//
// Animation.cpp for Zappy in /home/tuxlu/proj/PSU_2015_zappy/graph_dir
// 
// Made by Lucas Parsy
// Login   <parsy_a@epitech.net>
// 
// Started on  Wed Jun 22 22:15:06 2016 Lucas Parsy
// Last update Wed Jun 22 22:15:08 2016 Lucas Parsy
//

#include "Animation.hpp"

Animation::Animation() : m_texture(NULL)
{

}

void Animation::addFrame(sf::IntRect rect)
{
    m_frames.push_back(rect);
}

void Animation::setSpriteSheet(const sf::Texture& texture)
{
    m_texture = &texture;
}

const sf::Texture* Animation::getSpriteSheet() const
{
    return m_texture;
}

std::size_t Animation::getSize() const
{
    return m_frames.size();
}

const sf::IntRect& Animation::getFrame(std::size_t n) const
{
    return m_frames[n];
}
