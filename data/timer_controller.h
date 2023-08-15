#ifndef TIMER_CONTROLLER_H_INCLUDED
#define TIMER_CONTROLLER_H_INCLUDED

#pragma once
//#include <vector>
#include "elements/Timer.h"
#include <list>
#include <memory>

namespace data {
    class TimerController {
    public:
        virtual std::vector<Timer> getActiveTimers() { return std::vector<Timer>(); };
        const virtual std::list<std::shared_ptr<Timer>>& getAllTimers() const { return m_timers; }
        virtual void createTimer(std::string title) = 0;
    protected:
        std::list<std::shared_ptr<Timer>> m_timers;
    };

}

#endif