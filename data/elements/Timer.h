#ifndef TIMER_DATA_ELEMENT_H_INCLUDED
#define TIMER_DATA_ELEMENT_H_INCLUDED

#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
// MACROS can be defined for: Defining an end time value when timer is "active",
//  checking if timer is active.
using namespace std::chrono_literals;
constexpr std::chrono::time_point<std::chrono::system_clock> TIMER_RUNNING{0s};

namespace data {
    using std::chrono::system_clock;
    // TODO:- There should be an interface namespace Timer with limited constructor and methods that
    //      the backend controller translates for storage.
    class Timer {
    public:
        Timer(int id, system_clock::time_point date, std::string title, std::string comments,
            system_clock::time_point startTime, system_clock::time_point endTime = TIMER_RUNNING);

        int getId();
        system_clock::time_point getDate();
        std::string getTitle();
        std::string getComments();
        system_clock::time_point getStartTime();
        system_clock::time_point getEndTime();
        float getDuration();
        bool isRunning();
        void updateTime(system_clock::time_point time);

        static std::string dateToString(const std::chrono::time_point<system_clock>& time) {
            return std::vformat("{:%m/%d/%Y %H:%M}", std::make_format_args(time));
        };
        static std::string durationToString(const std::chrono::time_point<system_clock>& elapsed) {
            auto days = std::chrono::time_point_cast<std::chrono::days>(elapsed).time_since_epoch().count();
            auto secs = std::chrono::time_point_cast<std::chrono::seconds>(elapsed);
            std::stringstream ss;
            if (days > 0) ss << days << "d:";
            ss << std::vformat("{:%Hh:%Mm:%Ss}", std::make_format_args(secs));
            return ss.str();
            //return std::vformat("{:%m/%d/%Y %T}", std::make_format_args(hours));
        };
    private:
        int m_id;
        std::string m_title; // Title should eventually be replaced with "tasks"/"tags"
        system_clock::time_point m_date;
        system_clock::time_point m_startTime;
        system_clock::time_point m_endTime;
        std::string m_comments; // Will be its own data structure down the line
    };
}

#endif