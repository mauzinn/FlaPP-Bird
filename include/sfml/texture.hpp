#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <SFML\Graphics.hpp>

struct Texture {
    std::string source;
    sf::Texture texture_source;

    Texture(std::string _source, sf::Texture _texture_source);
};

#endif