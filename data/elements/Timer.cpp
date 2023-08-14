#include "Timer.h"

namespace data {

    Timer::Timer(int id, std::time_t date, std::string title, std::string comments,
        high_resolution_clock::time_point startTime, high_resolution_clock::time_point endTime) :
        m_id(id), m_date(date), m_title(title), m_comments(comments), m_startTime(startTime), m_endTime(endTime)
    {
    }

    int Timer::getId() {
        return m_id;
    }
    std::time_t Timer::getDate() {
        return m_date;
    }
    std::string Timer::getTitle() {
        return m_title;
    }
    std::string Timer::getComments() {
        return m_comments;
    }
    high_resolution_clock::time_point Timer::getStartTime() {
        return m_startTime;
    }
    high_resolution_clock::time_point Timer::getEndTime() {
        return m_endTime;
    }
    float Timer::getDuration() {
        std::chrono::duration<float, std::milli> elapsed = std::chrono::high_resolution_clock::now() - m_startTime;
        return elapsed.count();
    }
}