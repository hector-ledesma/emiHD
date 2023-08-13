#ifndef TIMER_DATA_ELEMENT_H_INCLUDED
#define TIMER_DATA_ELEMENT_H_INCLUDED

#pragma once
#include <string>
namespace data {
    // TODO:- There should be an interface namespace Timer with limited constructor and methods that
    //      the backend controller translates for storage.
    class Timer {
    public:
        std::string getDate();
        std::string getTitle();
        std::string getComments();
        std::string getStartTime();
        std::string getEndTime();
        std::string getDuration();
    private:
        std::string m_date;
        std::string m_title;
        std::string m_comments; // Will be its own data structure down the line
        std::string m_startTime;
        std::string m_endTime;
    };
}

#endif