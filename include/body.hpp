#ifndef BODY_HPP
#define BODY_HPP

#include "./vector2.hpp"

struct Body {
    Vector2 position, aceleration, size;
    bool is_colliding;
};

#endif