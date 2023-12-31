#ifndef DATA_CONTROLLER_H_INCLUDED
#define DATA_CONTROLLER_H_INCLUDED

#pragma once
#include <vector>
#include <set>
#include <memory>
#include "sqlite3.h"
#include "elements/Timer.h"
#include "TIMER_SET.h"
#include "DB_SCHEMA.h"
namespace data
{
    class DataController {
    public:
        DataController();
        ~DataController();
        void createTimer(std::string title);
        const TIMER_SET& getAllTimers(bool refetch);
        void updateState(std::shared_ptr<Timer> timer, TimerState_ changeTo);
    private:
        int id_count = 0; // Id will eventually be generated by the database
        TIMER_SET m_timers;
        sqlite3* m_dbHandle;
        sqlite3_stmt* m_createTable;
        sqlite3_stmt* m_timerInsert;
        sqlite3_stmt* m_timerUpdate;
        sqlite3_stmt* m_selectAll;

        void fetchTimers();
    };

}

#endif