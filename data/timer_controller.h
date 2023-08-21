#ifndef TIMER_CONTROLLER_H_INCLUDED
#define TIMER_CONTROLLER_H_INCLUDED

#pragma once
//#include <vector>
#include "elements/Timer.h"
#include "TIMER_SET.h"
#include <set>
#include <vector>

using std::shared_ptr;
namespace data {
    class TimerController {
    public:
        virtual std::vector<Timer> getActiveTimers() { return std::vector<Timer>(); };
        const virtual TIMER_SET& getAllTimers() const { return m_timers; }
        virtual void createTimer(std::string title) = 0;
    protected:
        TIMER_SET m_timers;
    };

}

#endif