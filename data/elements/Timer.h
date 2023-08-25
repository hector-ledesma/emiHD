#ifndef TIMER_DATA_ELEMENT_H_INCLUDED
#define TIMER_DATA_ELEMENT_H_INCLUDED

#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include "sqlite3.h"
#include "../DB_SCHEMA.h"

using namespace std::chrono_literals;
using std::chrono::system_clock;
constexpr std::chrono::system_clock::duration TIMER_RUNNING{0s};

// MACROS can be defined for: Defining an end time value when timer is "active",
//  checking if timer is active.
namespace {
}

namespace data {
    typedef std::chrono::system_clock clock;

    enum class TimerState_ {
        PAUSE,
        PLAY,
        STOP,
        PLAY_PAUSE // toggle based on previous state
    };

    enum class StatementType_ {
        INSERT,
        UPDATE
    };

    // TODO:- There should be an interface namespace Timer with limited constructor and methods that
    //      the backend controller translates for storage.
    class Timer {

        // A timer's duration will be subject to adjustments during its lifetime due to Play/Pause features. 
        // TimerDuration holds chrono timers and time state that track and apply these changes on state change.
        struct TimerDuration {
        public:
            TimerDuration(clock::time_point startTime, TimerState_ state);
            TimerDuration(clock::time_point startTime, clock::time_point elapsed, clock::time_point pausedAt, TimerState_ state);
            TimerState_ getState() const;
            clock::time_point getRuntime();
            clock::time_point getDuration();
            int bindToStmt(sqlite3_stmt* stmt);

            // Delete:
            clock::time_point getElapsed();
            clock::time_point getPausedAt();

            TimerState_ updateState(TimerState_ change_to);
        private:
            mutable TimerState_ m_state;
            mutable clock::time_point m_start;
            mutable clock::time_point m_elapsed;
            mutable clock::time_point m_pausedAt;
        };

    public:
        Timer(int id, clock::time_point date, std::string title, std::string comments,
            clock::time_point startTime, TimerState_ state = TimerState_::PLAY);
        Timer(int id, clock::time_point start, std::string title, clock::time_point duration, clock::time_point elapsed, clock::time_point paused, TimerState_ state);
        // This is a very fragile constructor. Functionality should be reformated to be more resilient
        int getId() const;
        clock::time_point getDate() const;
        std::string getTitle() const;
        std::string getComments() const;
        clock::time_point getStartTime() const;
        clock::time_point getRuntime();
        clock::time_point getDuration();
        // TODO: - Remove and bind inside of timer
        clock::time_point getPausedAt();
        clock::time_point getElapsed();
        TimerState_ getState() const;
        int bindToStmt(sqlite3_stmt* stmt, StatementType_ type);
        bool isRunning() const;
        //clock::duration getDuration();
        void togglePause();
        void stop();

        static std::string dateToString(const clock::time_point& time) {
            return std::vformat("{:%m/%d/%Y %H:%M}", std::make_format_args(time));
        };
        static std::string durationToString(const clock::time_point& elapsed) {
            auto days = std::chrono::time_point_cast<std::chrono::days>(elapsed).time_since_epoch().count();
            auto secs = std::chrono::time_point_cast<std::chrono::seconds>(elapsed);
            std::stringstream ss;
            if (days > 0) ss << days << "d:";
            ss << std::vformat("{:%Hh:%Mm:%Ss}", std::make_format_args(secs));
            return ss.str();
        };
        static Timer parse(sqlite3_stmt* stmt);
    private:
        int m_id;
        std::string m_title; // Title should eventually be replaced with "tasks"/"tags"
        clock::time_point m_date;
        std::string m_comments; // Will be its own data structure down the line
        TimerDuration m_duration;

        int bindToInsert(sqlite3_stmt* stmt);
        int bindToUpdate(sqlite3_stmt* stmt);
    };
}

#endif