#include "../include/vector2.hpp"

Vector2::Vector2(const int _x, const int _y) {
    Vector2::x = _x;
    Vector2::y = _y;
}

void Vector2::setVector(const Vector2 &_vector) {
    Vector2::x = _vector.x;
    Vector2::y = _vector.y;
}