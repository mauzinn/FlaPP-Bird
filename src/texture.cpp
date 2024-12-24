#include <iostream>
#include <SFML\Graphics.hpp>
#include "../include/sfml/texture.hpp"

Texture::Texture(std::string _source, sf::Texture _texture_source) {
    Texture::source = _source;
    Texture::texture_source = _texture_source;
}