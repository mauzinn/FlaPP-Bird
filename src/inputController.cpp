#include <vector>
#include "../include/key.hpp"
#include "../include/controllers/inputController.hpp"

int InputController::getIndex(const char _value) {
    for (int i = 0; i < InputController::keys_pressed.size(); i++) {
        if (InputController::keys_pressed[i].value == _value) {
            return _value;
        }
    }

    return -1;
}

InputController::InputController(std::vector<Key> _keys_allowed) {
    InputController::keys_allowed = _keys_allowed;
    InputController::isAnyKeyPressed = 0;
}

bool InputController::isKeyPressed(const char _value) {
    if (InputController::isAnyKeyPressed) {
        for (int i = 0; i < InputController::keys_pressed.size(); i++) {
            if (InputController::keys_pressed[i].value == _value) {
                return true;
            }
        }
    }

    return false;
}

void InputController::setKey(Key _new_key) {
    bool isAllowed = false;

    for (int i = 0; i < InputController::keys_allowed.size(); i++) {
        if (InputController::keys_allowed[i].value == _new_key.value) {
            isAllowed = true;
        }
    }

    if (isAllowed) {
        if (!InputController::isKeyPressed(_new_key.value)) {
            InputController::keys_pressed.push_back(_new_key);
            InputController::isAnyKeyPressed++;
        }
    }
}

void InputController::removeKey(Key _key) {
    if (InputController::isKeyPressed(_key.value)) {
        InputController::keys_pressed.erase(InputController::keys_pressed.begin() + InputController::getIndex(_key.value));
        InputController::isAnyKeyPressed--;
    }
}