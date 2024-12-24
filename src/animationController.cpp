#include <iostream>
#include <fstream>
#include "../include/controllers/animationController.hpp"
#include "../include/vector2.hpp"
#include "../include/sprite.hpp"

void AnimationController::nextIndex() {
    AnimationController::frame_index = (AnimationController::frame_index + 1) % AnimationController::frames;
}

std::string* AnimationController::getArchiveLines(const std::string _asset, const int _lines) {
    std::ifstream archive_data("assets/" + _asset + ".txt");
    std::string* buffer = new std::string[_lines];

    if (archive_data.is_open()) {
        for (int i = 0; i < _lines; i++) {
            std::getline(archive_data, buffer[i]);
            std::cout << buffer[i] << '\n';
        }
        archive_data.close();
    }

    return buffer;
}

void AnimationController::setTexture(std::string _asset, bool _animated) {
    if (_asset.size()) {
        AnimationController::source = "assets/" + _asset + ".png";
        std::string* buffer = AnimationController::getArchiveLines(_asset, 3);

        AnimationController::animated = _animated;
        AnimationController::frame_size.setVector(Vector2(std::stoi(buffer[0]), std::stoi(buffer[1])));
        AnimationController::frames = std::stoi(buffer[2]) / std::stoi(buffer[0]);
        AnimationController::frame_index = 0;
        delete[] buffer;
    }
}

AnimationController::AnimationController(std::string _asset, bool _animated) {
    AnimationController::frame_index = 0;
    AnimationController::setTexture(_asset, _animated);
}

void AnimationController::update() {
    if (AnimationController::animated) {
        AnimationController::nextIndex();
    }
}

Sprite AnimationController::getSprite() {
    return Sprite(AnimationController::source, AnimationController::frame_size, AnimationController::frames, AnimationController::frame_index);
}