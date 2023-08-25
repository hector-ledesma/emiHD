#ifndef TIMER_INTERFACE_ELEMENT_H_INCLUDED
#define TIMER_INTERFACE_ELEMENT_H_INCLUDED

#pragma once
#include <memory>
#include "element.h"
#include "../data/elements/Timer.h"
#include "../data/data_controller.h"

#define TIMER_ELEMENT_ID "timer_element##"
namespace UI {
    class Timer : public Element {
    public:
        Timer(ImGuiWindowFlags flags, const std::shared_ptr<data::Timer> timer, const std::shared_ptr<data::DataController> data);
    protected:
        bool begin();
        void end();
        void style();
    private:
        std::shared_ptr<data::Timer> m_timer;
        std::shared_ptr<data::DataController> m_data;
        bool m_paused = false;
    };
}
#endif