#include <chrono>
#include "../include/controllers/timeController.hpp"

TimeController::TimeController(int _frames) {
    TimeController::frames = _frames;
    TimeController::last_time = std::chrono::high_resolution_clock::now();
}

bool TimeController::canUpdate() {
    std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - TimeController::last_time);

    if (elapsed_time.count() >= int(1000 / TimeController::frames)) {
        TimeController::last_time = current_time;
        return true;
    }
    return false;
}