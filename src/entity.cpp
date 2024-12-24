#include <iostream>
#include "../include/entity/entity.hpp"
#include "../include/vector2.hpp"
#include "../include/sprite.hpp"
#include "../include/body.hpp"

Entity::Entity(Body _body, std::string _asset, bool _animated) {
    Entity::animation.setTexture(_asset, _animated);
    Entity::body = _body;
}

void Entity::update() {
    Entity::animation.update();
}

void Entity::setColliding(bool _is_colliding) {
    Entity::body.is_colliding = _is_colliding;
}

void Entity::setPosition(Vector2 _vector) {
    Entity::body.position = _vector;
}

void Entity::setSize(Vector2 _vector) {
    Entity::body.size = _vector;
}

void Entity::setAceleration(Vector2 _vector) {
    Entity::body.aceleration = _vector;
}

bool Entity::getColliding() {
    return Entity::body.is_colliding;
}

Vector2 Entity::getPosition() {
    return Entity::body.position;
}

Vector2 Entity::getSize() {
    return Entity::body.size;
}

Vector2 Entity::getAceleration() {
    return Entity::body.aceleration;
}

Sprite Entity::getSprite() {
    return Entity::animation.getSprite();
}