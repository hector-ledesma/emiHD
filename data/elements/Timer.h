#ifndef TIMER_DATA_ELEMENT_H_INCLUDED
#define TIMER_DATA_ELEMENT_H_INCLUDED

#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>

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
        STOP
    };

    // TODO:- There should be an interface namespace Timer with limited constructor and methods that
    //      the backend controller translates for storage.
    class Timer {

        // A timer's duration will be subject to adjustments during its lifetime due to Play/Pause features. 
        // TimerDuration holds chrono timers and time state that track and apply these changes on state change.
        struct TimerDuration {
        public:
            TimerDuration(clock::time_point startTime, TimerState_ state);
            TimerState_ getState() const;
            clock::time_point getRuntime();
            clock::time_point getDuration();
            TimerState_ updateState(TimerState_ change_to);
        private:
            mutable TimerState_ m_state;
            mutable clock::time_point m_elapsed;
            mutable clock::time_point m_start;
            mutable clock::time_point m_pausedAt;
        };

    public:
        Timer(int id, clock::time_point date, std::string title, std::string comments,
            clock::time_point startTime, TimerState_ state = TimerState_::PLAY);

        int getId() const;
        clock::time_point getDate() const;
        std::string getTitle() const;
        std::string getComments() const;
        clock::time_point getStartTime() const;
        clock::time_point getRuntime();
        clock::time_point getDuration();
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
    private:
        int m_id;
        std::string m_title; // Title should eventually be replaced with "tasks"/"tags"
        clock::time_point m_date;
        TimerDuration m_duration;
        std::string m_comments; // Will be its own data structure down the line
    };
}

#endif