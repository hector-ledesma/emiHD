#include "data_controller.h"

#include <ctime>
#include <chrono>
#include <memory>
#include <iostream>
#include <assert.h>
#include <unordered_map>
#include "elements/Timer.h"


namespace data {
    DataController::DataController() : m_createTable{ nullptr }, m_timerInsert{ nullptr }, m_timerUpdate{ nullptr }, m_selectAll{ nullptr } {
        int rc = sqlite3_open_v2("emiHD.db", &m_dbHandle, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
        sqlite3_prepare_v2(m_dbHandle, DB_SCHEMA.c_str(), DB_SCHEMA.size() + 1, &m_createTable, nullptr);
        sqlite3_step(m_createTable);
    }
    DataController::~DataController() {
        sqlite3_finalize(m_createTable);
        sqlite3_finalize(m_timerInsert);
        sqlite3_finalize(m_timerUpdate);
        sqlite3_finalize(m_selectAll);
        sqlite3_close(m_dbHandle);
    }


    void DataController::createTimer(std::string title) {
        int rc = SQLITE_OK;
        if (m_timerInsert == nullptr) {
            rc = sqlite3_prepare_v2(m_dbHandle, INSERT_QUERY.c_str(), INSERT_QUERY.size() + 1, &m_timerInsert, nullptr);
            assert (rc == SQLITE_OK);
        }
        sqlite3_reset(m_timerInsert);
        auto now = std::chrono:: system_clock::now();
        // Of format:
        //    INSERT INTO TIMERS (TITLE, START_DATE, STATE, DURATION, ELAPSED, PAUSED) VALUES (?, ?, ?, ?, ?, ?)
        rc = sqlite3_bind_text(m_timerInsert, 1, title.c_str(), title.size() + 1, SQLITE_TRANSIENT);
        assert (rc == SQLITE_OK);
        rc = sqlite3_bind_int64(m_timerInsert, 2, now.time_since_epoch().count());
        assert (rc == SQLITE_OK);
        std::string state{ "PLAY" };
        rc = sqlite3_bind_text(m_timerInsert, 3, state.c_str(), state.size() + 1, SQLITE_TRANSIENT);
        assert (rc == SQLITE_OK);
        rc = sqlite3_bind_int64(m_timerInsert, 4, now.time_since_epoch().count());
        assert(rc == SQLITE_OK);
        rc = sqlite3_step(m_timerInsert);
        if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
            std::cout << "Failed to insert. " << "RC: " << rc << " msg: " << sqlite3_errmsg(m_dbHandle) << "\n";
            assert(false);
        }
        fetchTimers();
    }
    
    const TIMER_SET& DataController::getAllTimers(bool refetch) { 
        if (refetch) {
            fetchTimers();
        }
        return m_timers;
    }
    void DataController::updateState(std::shared_ptr<Timer> timer, TimerState_ changeTo) {
        if (m_timerUpdate == nullptr) {
            int rc = sqlite3_prepare_v2(m_dbHandle, UPDATE_QUERY.c_str(), UPDATE_QUERY.size() + 1, &m_timerUpdate, nullptr);
            if (rc != SQLITE_OK) {
                std::cout << "Failed to insert. " << "RC: " << rc << " msg: " << sqlite3_errmsg(m_dbHandle) << "\n";
                assert(false);
            }
        }
        sqlite3_reset(m_timerUpdate);

        switch (changeTo)
        {
        case TimerState_::STOP:
            timer->stop();
            break;
        case TimerState_::PLAY_PAUSE:
            timer->togglePause();
            break;
        default:
            assert(false); // This should never be called with any other values yet
            break;
        }
        assert (timer->bindToStmt(m_timerUpdate, StatementType_::UPDATE) == SQLITE_OK);
        int rc = sqlite3_step(m_timerUpdate);
        if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
            std::cout << "Failed to insert. " << "RC: " << rc << " msg: " << sqlite3_errmsg(m_dbHandle) << "\n";
            assert(false);
        }
    }

    void DataController::fetchTimers() {
        if (m_selectAll == nullptr) {
            int rc = sqlite3_prepare_v2(m_dbHandle, SELECT_QUERY.c_str(), SELECT_QUERY.size() + 1, &m_selectAll, nullptr);
            assert (rc == SQLITE_OK);
        }
        sqlite3_reset(m_selectAll);
        while (sqlite3_step(m_selectAll) == SQLITE_ROW) {
            auto timer = Timer::parse(m_selectAll);
            m_timers.insert(std::make_shared<Timer>(timer));
        }

    }

}