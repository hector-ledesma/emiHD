#ifndef TIMER_CONTROLLER_H_INCLUDED
#define TIMER_CONTROLLER_H_INCLUDED

#pragma once
#include <vector>
#include "elements/Timer.h"
namespace data {
    class TimerController {
    public:
        virtual std::vector<Timer> getActiveTimers() { return std::vector<Timer>(); };
        virtual std::vector<Timer> getAllTimers() { return std::vector<Timer>(); }
        virtual void createTimer(std::string title) = 0;
    private:
    };

}

#endif