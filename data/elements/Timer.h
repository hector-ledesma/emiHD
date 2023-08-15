#ifndef TIMER_DATA_ELEMENT_H_INCLUDED
#define TIMER_DATA_ELEMENT_H_INCLUDED

#pragma once
#include <string>
#include <chrono>
#include <ctime>
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
        Timer(int id, std::time_t date, std::string title, std::string comments,
            system_clock::time_point startTime, system_clock::time_point endTime = TIMER_RUNNING);

        int getId();
        std::time_t getDate();
        std::string getTitle();
        std::string getComments();
        system_clock::time_point getStartTime();
        system_clock::time_point getEndTime();
        float getDuration();
        bool isRunning();
    private:
        int m_id;
        std::string m_title; // Title should eventually be replaced with "tasks"/"tags"
        std::time_t m_date;
        system_clock::time_point m_startTime;
        system_clock::time_point m_endTime;
        std::string m_comments; // Will be its own data structure down the line
    };
}

#endif