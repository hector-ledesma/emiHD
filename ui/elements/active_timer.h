#ifndef TIMER_INTERFACE_ELEMENT_H_INCLUDED
#define TIMER_INTERFACE_ELEMENT_H_INCLUDED

#pragma once
#include "element.h"
#include "../data/elements/Timer.h"

#define TIMER_ELEMENT_ID "timer_element##"
namespace UI {
    class Timer : public Element {
    public:
        Timer(ImGuiWindowFlags flags, const std::shared_ptr<data::Timer> timer);
    protected:
        bool begin();
        void end();
        void style();
    private:
        std::shared_ptr<data::Timer> m_timer;
        bool m_paused = false;
    };
}
#endif