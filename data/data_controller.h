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
        //std::vector<Timer> getActiveTimers();
        //std::vector<Timer>& getAllTimers();
        void createTimer(std::string title);
    private:
        //std::vector<Timer> m_timers;
        int id_count = 0; // Id will eventually be generated by the database
    };

}

#endif