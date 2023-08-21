#ifndef HISTORY_TABLE_INTERFACE_ELEMENT_H_INCLUDED
#define HISTORY_TABLE_INTERFACE_ELEMENT_H_INCLUDED

#pragma once
#include "element.h"
#include <set>
//#include <list>
#include "../data/elements/Timer.h"
#include "../data/TIMER_SET.h"

#define HISTORY_TABLE_ID "history_table"
namespace UI {
    class HistoryTable : public Element {
    public:
        HistoryTable(ImGuiWindowFlags flags, const TIMER_SET& timers);
    protected:
        bool begin();
        void end();
        void style();
    private:
        TIMER_SET m_timers;
    };
}
#endif