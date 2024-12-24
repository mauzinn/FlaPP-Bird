#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include "../controllers/animationController.hpp"
#include "../vector2.hpp"
#include "../sprite.hpp"
#include "../body.hpp"

class Entity {
    private:
    AnimationController animation;
    Body body;

    public:
    Entity(Body _body, std::string _asset, bool _animated);
    void update();

    void setColliding(bool _is_colliding);
    void setPosition(Vector2 _vector);
    void setSize(Vector2 _vector);
    void setAceleration(Vector2 _vector);

    bool getColliding();
    Vector2 getPosition();
    Vector2 getSize();
    Vector2 getAceleration();
    Sprite getSprite();
};

#endif