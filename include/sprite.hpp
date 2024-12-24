#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <iostream>
#include "./vector2.hpp"

struct Sprite {
    std::string source;
    Vector2 frame_size;
    int frames, current_frame;

    Sprite(std::string _source, Vector2 _frame_size, int _frames, int _current_frame);
};

#endif