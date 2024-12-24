#include <iostream>
#include "../include/sprite.hpp"

Sprite::Sprite(std::string _source, Vector2 _frame_size, int _frames, int _current_frame) {
    Sprite::source = _source;
    Sprite::frame_size = _frame_size;
    Sprite::frames = _frames;
    Sprite::current_frame = _current_frame;

    std::cout << "-->Sprite<-- New Sprite has been Drawned from Source: " << _source << '\n';
}