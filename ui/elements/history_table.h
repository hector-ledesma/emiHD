#ifndef HISTORY_TABLE_INTERFACE_ELEMENT_H_INCLUDED
#define HISTORY_TABLE_INTERFACE_ELEMENT_H_INCLUDED

#pragma once
#include "element.h"
#include <vector>
#include "../data/elements/Timer.h"

#define HISTORY_TABLE_ID "history_table"
namespace UI {
    class HistoryTable : public Element {
    public:
        HistoryTable(ImGuiWindowFlags flags, std::vector<data::Timer> timers);
    protected:
        bool begin();
        void end();
        void style();
    private:
        std::vector<data::Timer> m_timers;
    };
}
#endif