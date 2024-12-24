#ifndef INPUTCONTROLLER_HPP
#define INPUTCONTROLLER_HPP

#include <vector>
#include "../key.hpp"

class InputController {
    private:
    std::vector<Key> keys_allowed, keys_pressed;
    int isAnyKeyPressed;

    int getIndex(const char _value);
    public:
    InputController(std::vector<Key> _keys_allowed);

    void setKey(Key _new_key);
    void removeKey(Key _key);
    bool isKeyPressed(const char _value);
};

#endif