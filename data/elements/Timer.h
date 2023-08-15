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
constexpr std::chrono::system_clock::duration TIMER_RUNNING{0s};

namespace data {
    using std::chrono::system_clock;
    // TODO:- There should be an interface namespace Timer with limited constructor and methods that
    //      the backend controller translates for storage.
    class Timer {
    public:
        Timer(int id, system_clock::time_point date, std::string title, std::string comments,
            system_clock::time_point startTime, system_clock::duration duration = TIMER_RUNNING);

        int getId() const;
        system_clock::time_point getDate() const;
        std::string getTitle() const;
        std::string getComments() const;
        system_clock::time_point getStartTime() const;
        system_clock::duration getDuration() const;
        bool isRunning() const;
        void updateTime(system_clock::time_point time) const;
        void setDuration(system_clock::duration duration) const;

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
        mutable system_clock::time_point m_startTime;
        mutable system_clock::duration m_duration;
        std::string m_comments; // Will be its own data structure down the line
    };
}

#endif