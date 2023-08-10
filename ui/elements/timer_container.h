#ifndef TIMER_CONTAINER_INCLUDED
#define TIMER_CONTAINER_INCLUDED

#pragma once
#define TIMER_CONTAINER_ID "timer_container"

#include "element.h"
#include "imgui.h"

namespace UI {
    // TODO:- TimerContainer to take in lambdas for the buttons?
    //        Or leave that functionality for the interface controller?
    class TimerContainer : public Element {
    public:
        TimerContainer(ImGuiWindowFlags flags);
    protected:
        bool begin();
        void end();
        void style();
    };
}
#endif