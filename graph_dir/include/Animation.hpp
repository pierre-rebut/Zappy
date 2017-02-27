//
// Animation.hpp for Zappy in /home/tuxlu/proj/PSU_2015_zappy/graph_dir
// 
// Made by Lucas Parsy
// Login   <parsy_a@epitech.net>
// 
// Started on  Wed Jun 22 15:41:05 2016 Lucas Parsy
// Last update Wed Jun 22 15:41:52 2016 Lucas Parsy
//

#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

class Animation
{
public:
    Animation();

    void addFrame(sf::IntRect rect);
    void setSpriteSheet(const sf::Texture& texture);
    const sf::Texture* getSpriteSheet() const;
    std::size_t getSize() const;
    const sf::IntRect& getFrame(std::size_t n) const;

private:
    std::vector<sf::IntRect> m_frames;
    const sf::Texture* m_texture;
};

#endif // _ANIMATION_HPP_
