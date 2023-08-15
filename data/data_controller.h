#ifndef DATA_CONTROLLER_H_INCLUDED
#define DATA_CONTROLLER_H_INCLUDED

#pragma once
#include <vector>
#include "timer_controller.h"

namespace data
{
    class DataController : public TimerController {
    public:
        DataController();
        ~DataController();
        std::vector<Timer> getActiveTimers();
        std::vector<Timer> getAllTimers();
    private:
        std::vector<Timer> m_timers;
    };

}

#endif