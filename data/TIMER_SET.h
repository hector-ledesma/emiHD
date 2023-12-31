#ifndef TIMER_SET_H_
#define TIMER_SET_H_

#pragma once
#include <set>
#include <memory>
#include "elements/Timer.h"

struct test {
    bool operator() (const std::shared_ptr<data::Timer> a, const std::shared_ptr<data::Timer> b) const {
        bool bothrunning = a->isRunning() && b->isRunning();
        bool bothstopped = !a->isRunning() && !b->isRunning();
        bool isearlier = a->getStartTime() > b->getStartTime();
        if (bothrunning || bothstopped) {
            if (a->getStartTime() == b->getStartTime()) {
                return a->getId() > b->getId();
            }
            return isearlier;
        }
        
        return a->isRunning();
        //return a->getStartTime() == b->getStartTime() ? a->getId() > b->getId() : a->isRunning() && !b->isRunning() || a->getStartTime() > b->getStartTime();
    }
};

typedef std::set<std::shared_ptr<data::Timer>, test> TIMER_SET;

#endif