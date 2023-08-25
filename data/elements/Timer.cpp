#include "Timer.h"
#include <iostream>
namespace {
}
namespace data {
    // Timer::TimerDuration
    Timer::TimerDuration::TimerDuration(clock::time_point startTime, TimerState_ state) : m_state(state), m_start(startTime) {

    }
    Timer::TimerDuration::TimerDuration(clock::time_point startTime, clock::time_point elapsed, clock::time_point pausedAt, TimerState_ state) : m_state(state), m_start(startTime), m_elapsed(elapsed), m_pausedAt(pausedAt) {

    }

    TimerState_ Timer::TimerDuration::getState() const {
        return m_state;
    }
    clock::time_point Timer::TimerDuration::getDuration() {
        return m_start;
    }
    clock::time_point Timer::TimerDuration::getRuntime() {
        switch (m_state) {
        case data::TimerState_::PAUSE:
            return m_elapsed;
            break;
        case data::TimerState_::PLAY:
            return clock::time_point{ clock::now() - m_start };
            break;
        default:
            break;
        }
    }

    TimerState_ Timer::TimerDuration::updateState(TimerState_ change_to) {
        switch (change_to)
        {
        case data::TimerState_::PAUSE:
            m_pausedAt = clock::now();
            m_elapsed = clock::time_point{ m_pausedAt - m_start };
            break;
        case data::TimerState_::PLAY:
            m_start = clock::time_point{ clock::now() - m_elapsed };
            break;
        case data::TimerState_::STOP:
            if (m_state == TimerState_::PAUSE) m_start = clock::time_point{ clock::now() - m_elapsed };
            m_start = clock::time_point{ clock::now() - m_start };
            break;
        default:
            break;
        }
        m_state = change_to;
        return getState();
    }

    clock::time_point Timer::TimerDuration::getElapsed() {
        return m_elapsed;
    }
    clock::time_point Timer::TimerDuration::getPausedAt() {
        return m_pausedAt;
    }

    int Timer::TimerDuration::bindToStmt(sqlite3_stmt* stmt) {
        int rc = SQLITE_OK;
        std::string state = "STOP";
        switch (m_state)
        {
        case TimerState_::PAUSE:
            state = "PAUSE";
            break;
        case TimerState_::PLAY:
            state = "PLAY";
            break;
        default:
            break;
        }
        rc = sqlite3_bind_text(stmt, static_cast<update_val>(UPDATE_BINDING::STATE), state.c_str(), state.size() + 1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) return rc;
        // Bind Duration
        rc = sqlite3_bind_int64(stmt, static_cast<update_val>(UPDATE_BINDING::DURATION), m_start.time_since_epoch().count());
        if (rc != SQLITE_OK) return rc;
        // Bind Elapsed
        rc = sqlite3_bind_int64(stmt, static_cast<update_val>(UPDATE_BINDING::ELAPSED), m_elapsed.time_since_epoch().count());
        if (rc != SQLITE_OK) return rc;
        // Bind Paused
        rc = sqlite3_bind_int64(stmt, static_cast<update_val>(UPDATE_BINDING::PAUSED), m_pausedAt.time_since_epoch().count());
        return rc;
    }


    // Timer
    Timer::Timer(int id, system_clock::time_point date, std::string title, std::string comments,
        system_clock::time_point startTime, TimerState_ state) :
        m_id(id), m_date(date), m_title(title), m_comments(comments), m_duration{startTime, state}
    {
    }

    Timer::Timer(int id, clock::time_point start, std::string title, clock::time_point duration, clock::time_point elapsed, clock::time_point paused, TimerState_ state) : m_id(id), m_date(start), m_title(title), m_comments{ "" }, m_duration{duration, elapsed, paused, state} {

    }

    int Timer::bindToInsert(sqlite3_stmt* stmt) {
        return 0;
    }
    int Timer::bindToUpdate(sqlite3_stmt* stmt) {
        using std::string;
        int rc = SQLITE_OK;
        // Bind ID
        rc = sqlite3_bind_int(stmt, static_cast<update_val>(UPDATE_BINDING::ID), m_id);
        if (rc != SQLITE_OK) return rc;
        // Bind title
        rc = sqlite3_bind_text(stmt, static_cast<update_val>(UPDATE_BINDING::TITLE), m_title.c_str(), m_title.size() + 1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) return rc;

        // Bind Duration values
        return m_duration.bindToStmt(stmt);
    }
    int Timer::bindToStmt(sqlite3_stmt* stmt, StatementType_ type) {
        switch (type)
        {
        case data::StatementType_::INSERT:
            return bindToInsert(stmt);
            break;
        case data::StatementType_::UPDATE:
            return bindToUpdate(stmt);
            break;
        }
    }

    int Timer::getId() const {
        return m_id;
    }
    system_clock::time_point Timer::getDate() const {
        return m_date;
    }
    std::string Timer::getTitle() const {
        return m_title;
    }
    std::string Timer::getComments() const {
        return m_comments;
    }
    system_clock::time_point Timer::getStartTime() const {
        return m_date;
    }
    system_clock::time_point Timer::getRuntime() {
        auto runtime = m_duration.getRuntime();

        return clock::time_point{ runtime };
    }
    system_clock::time_point Timer::getDuration() {
        auto duration = m_duration.getDuration();

        return clock::time_point{ duration };
    }
    
    bool Timer::isRunning() const {
        return m_duration.getState() != TimerState_::STOP;
    }

    void Timer::togglePause() {
        if (m_duration.getState() == TimerState_::PAUSE) {
            m_duration.updateState(TimerState_::PLAY);
        }
        else {
            m_duration.updateState(TimerState_::PAUSE);
        }
    }

    void Timer::stop() {
        m_duration.updateState(TimerState_::STOP);
    }

    TimerState_ Timer::getState() const {
        return m_duration.getState();
    }
    clock::time_point Timer::getElapsed() {
        return m_duration.getElapsed();
    }
    clock::time_point Timer::getPausedAt() {
        return m_duration.getPausedAt();
    }

    Timer Timer::parse(sqlite3_stmt* stmt) {
        int id = sqlite3_column_int(stmt, 0);
        std::string title((char*)sqlite3_column_text(stmt, 1));
        long long start_count = sqlite3_column_int64(stmt, 2);
        auto start = system_clock::time_point{ system_clock::duration(start_count) };

        // TimerDuration
        std::string state_v((char*)sqlite3_column_text(stmt, 3));
        data::TimerState_ state = data::TimerState_::STOP;
        if (state_v == "PLAY") state = data::TimerState_::PLAY;
        else if (state_v == "PAUSE") state = data::TimerState_::PAUSE;
        long long duration_count = sqlite3_column_int64(stmt, 4);
        auto duration = system_clock::time_point{ system_clock::duration(duration_count) };
        long long elapsed_count = sqlite3_column_int64(stmt, 5);
        auto elapsed = system_clock::time_point{ system_clock::duration(elapsed_count) };
        long long paused_count = sqlite3_column_int64(stmt, 6);
        auto paused = system_clock::time_point{ system_clock::duration(paused_count) };

        return Timer(id, start, title, duration, elapsed, paused, state);
    }
}