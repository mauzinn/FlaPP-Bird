#ifndef ANIMATIONCONTROLLER_HPP
#define ANIMATIONCONTROLLER_HPP

#include <iostream>
#include "../vector2.hpp"
#include "../sprite.hpp"

class AnimationController {
    private:
    std::string source;
    Vector2 frame_size;
    bool animated;
    int frames, frame_index;

    void nextIndex();
    std::string* getArchiveLines(const std::string _asset, const int _lines);
    public:
    AnimationController(std::string _asset = "", bool _animated = false);
    void update();
    
    void setTexture(std::string _asset, bool _animated);
    Sprite getSprite();
};

#endif