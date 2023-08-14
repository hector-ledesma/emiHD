#ifndef TIMER_DATA_ELEMENT_H_INCLUDED
#define TIMER_DATA_ELEMENT_H_INCLUDED

#pragma once
#include <string>
#include <chrono>
#include <ctime>


namespace data {
    using std::chrono::high_resolution_clock;
    // TODO:- There should be an interface namespace Timer with limited constructor and methods that
    //      the backend controller translates for storage.
    class Timer {
    public:
        Timer(int id, std::time_t date, std::string title, std::string comments,
            high_resolution_clock::time_point startTime, high_resolution_clock::time_point endTime);

        int getId();
        std::time_t getDate();
        std::string getTitle();
        std::string getComments();
        high_resolution_clock::time_point getStartTime();
        high_resolution_clock::time_point getEndTime();
        float getDuration();
    private:
        int m_id;
        std::string m_title;
        std::time_t m_date;
        high_resolution_clock::time_point m_startTime;
        high_resolution_clock::time_point m_endTime;
        std::string m_comments; // Will be its own data structure down the line
    };
}

#endif