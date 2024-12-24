#ifndef VECTOR2_HPP
#define VECTOR2_HPP

struct Vector2 {
    int x, y;

    Vector2(const int _x = 0, const int _y = 0);
    void setVector(const Vector2 &_vector);
};

#endif