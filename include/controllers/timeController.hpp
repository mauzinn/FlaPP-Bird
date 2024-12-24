#ifndef TIMECONTROLLER_HPP
#define TIMECONTROLLER_HPP

#include <chrono>

struct TimeController {
    std::chrono::high_resolution_clock::time_point last_time;
    int frames;

    TimeController(int _frames);
    bool canUpdate();
};

#endif